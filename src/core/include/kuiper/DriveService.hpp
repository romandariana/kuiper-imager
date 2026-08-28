#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>

#include "kuiper/Drive.hpp"
#include "kuiper/Error.hpp"
#include "kuiper/MountedPartition.hpp"
#include "kuiper/Progress.hpp"
#include "kuiper/platform/IDriveBackend.hpp"

namespace kuiper {

// Wall-clock breakdown of a flash, in seconds. A diagnostic surface: it lets us
// see where the time actually goes (write vs verify) and A/B every performance
// change. The two informative splits are decompress-vs-deviceWrite (does a
// decompress/write pipeline help? the gain is min(decompress, deviceWrite)) and
// deviceWrite-vs-flush (under O_DIRECT the device time lands in the write step;
// buffered I/O would push it into flush). All steady_clock; overhead is a few
// clock reads per chunk.
struct FlashTimings {
    double prepareSec = 0;      // unmount + open + wipe signatures
    double writeSec = 0;        // step 7 wall time (decompress + device write, serialized)
    double decompressSec = 0;   //   of which: archive_read_data
    double deviceWriteSec = 0;  //   of which: dev.write (memcpy + O_DIRECT pwrite)
                                //   residual (writeSec - the two above) = hashing + copies
    double flushSec = 0;        // step 8 flushAndSync (fsync)
    double verifySec = 0;       // step 9 body read-back + hash compare
    double headSec = 0;         // steps 10-11 commit + verify partition table
    double totalSec = 0;        // whole flash() call
};

// Result of a successful flash: bytes written and the SHA-256 of the
// decompressed image (verified against a read-back of the device).
struct FlashSummary {
    std::uint64_t bytesWritten = 0;
    std::string sha256;  // lowercase hex
    // Set by flash(); left empty by writePreloader (which shares this type).
    std::optional<FlashTimings> timings;
};

// Options for a raw write to a block target — shared by flash() and
// writePreloader(). Both fields default to the safe setting.
struct WriteOptions {
    // Bypass the target-safety guards: presence + removable/system for a whole
    // disk (flash), and additionally the mounted-partition check for a partition
    // (writePreloader). Needed for loopback devices (/dev/loopN) and power users;
    // the backend still refuses anything that isn't a block device. USE WITH CARE
    // — this is the guard that stops you erasing a disk.
    bool force = false;

    // Read the target back and compare SHA-256 after writing. On by default; the
    // integrity guarantee that distinguishes us from raw dd. For flash(), turning
    // it off skips only the full-image read-back (~half the wall time) — the
    // partition table is still written last and checked, so a failed flash never
    // looks bootable.
    bool verify = true;
};

class DriveService {
public:
    DriveService();
    explicit DriveService(std::unique_ptr<IDriveBackend> backend);

    // Enumerate storage drives, each with its partitions filled in.
    Result<DriveList> listDrives();

    // Mount a partition (e.g. the identified BOOT) and return an RAII handle to
    // its filesystem path. Thin passthrough to the backend so front-ends never
    // reach past the service. The handle borrows an existing mount or owns one
    // it creates; either way the mount is valid for the handle's lifetime.
    Result<MountedPartition> mount(const Partition& partition);

    // Flash a local image file (raw or .zip/.xz/.zst/.gz) onto `driveNode`,
    // then verify by reading it back and comparing SHA-256. Blocking; reports
    // progress via `onProgress` and polls `cancel` between chunks.
    Result<FlashSummary> flash(const std::string& driveNode,
                               const std::string& imagePath,
                               const WriteOptions& options = {},
                               ProgressFn onProgress = {},
                               CancelToken cancel = {});

    // Raw-write an (uncompressed) preloader blob to a partition and verify it by
    // read-back. This is the intel-only device step of `configure`; it goes here
    // so ConfigurationService stays portable. The caller supplies the partition
    // node from the identified layout (Layout.hpp), never a composed string.
    // Refuses a mounted or non-removable target unless options.force.
    Result<FlashSummary> writePreloader(const std::string& partitionDevice,
                                        const std::string& preloaderFile,
                                        const WriteOptions& options = {},
                                        ProgressFn onProgress = {},
                                        CancelToken cancel = {});

    const char* backendName() const noexcept;

private:
    std::unique_ptr<IDriveBackend> backend_;
};

}  // namespace kuiper
