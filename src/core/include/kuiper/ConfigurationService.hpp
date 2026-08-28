#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "kuiper/Error.hpp"
#include "kuiper/Progress.hpp"
#include "kuiper/Project.hpp"

namespace kuiper {

// Injected raw preloader writer. `configureProject` calls this for intel
// projects instead of touching a drive itself, keeping ConfigurationService 100%
// portable. The composition root (CLI) wires it to DriveService::writePreloader.
using PreloaderSink =
    std::function<Result<void>(const std::string& preloaderFile, ProgressFn)>;

// Options for configureProject.
struct ConfigureOptions {
    bool dryRun = false;  // compute the copy plan without touching the card
};

// One boot file that configure copies into the boot-partition root.
struct CopyOp {
    std::string source;  // absolute path within the boot partition
    std::string dest;    // absolute path at the boot-partition root
};

// What configureProject did (or, in dry-run, would do).
struct ConfigureSummary {
    std::vector<CopyOp> files;
    bool dryRun = false;
    std::optional<std::string> preloader;  // resolved source, intel only
};

// Reads and (later) applies the ADI boot-file configuration that lives on the
// mounted BOOT partition. This is the C++ port of configure-setup.sh.
//
// Path-based by design: the manifests are files inside the FAT BOOT filesystem,
// so the partition must already be mounted. This keeps the service 100%
// portable (std::filesystem + Qt JSON, no platform code). The CLI's openBoot()
// helper resolves a drive to its mounted BOOT path and passes it in here.
class ConfigurationService {
public:
    ConfigurationService() = default;

    // Recursively scan `bootPath` for *.json manifests and collect every
    // project they declare. Mirrors the script's listing: non-manifest or
    // malformed JSON is skipped silently; a valid directory with no projects
    // yields an empty list (not an error). A missing or non-directory path is
    // an error.
    Result<ProjectList> listProjects(const std::string& bootPath = "/boot");

    // Find the project matching `name` + `board` on `bootPath`. Reuses the
    // listProjects scan; the first match wins (faithful to the script's
    // `head -n 1`). Returns NotFound if no project matches.
    Result<Project> findProject(const std::string& bootPath,
                                const std::string& name,
                                const std::string& board);

    // Apply a project's boot files: copy its kernel and files[] from their
    // subdirectories into the boot-partition root (where the board's bootloader
    // looks). 100% portable file operations. Fails fast — if any source is
    // missing the card is left untouched. Intel projects additionally need a raw
    // preloader write to the bootloader partition: pass `writePreloader` to
    // perform it (the CLI wires it to DriveService). Without a sink, intel
    // projects return UnsupportedPlatform + the manual procedure.
    Result<ConfigureSummary> configureProject(const std::string& bootPath,
                                              const Project& project,
                                              const ConfigureOptions& opts = {},
                                              ProgressFn onProgress = {},
                                              PreloaderSink writePreloader = {});

    const char* backendName() const noexcept;
};

}  // namespace kuiper
