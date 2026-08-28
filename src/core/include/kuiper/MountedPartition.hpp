#pragma once

#include <functional>
#include <string>
#include <utility>

namespace kuiper {

// RAII handle to a partition that is mounted and readable at `path()`. Ownership
// is honest: it unmounts ONLY what Kuiper Imager itself mounted. If the
// partition was already mounted (e.g. a desktop auto-mounted BOOT), the handle
// is "borrowed" — it holds no unmounter and leaves the mount alone on
// destruction.
//
// Move-only; the backend's mount() is the sole producer (see IDriveBackend).
class MountedPartition {
public:
    MountedPartition() = default;

    // `unmount` runs once on destruction (or move-assignment over this handle).
    // Pass an empty std::function for a borrowed mount that must not be touched.
    MountedPartition(std::string path, std::function<void()> unmount)
        : path_(std::move(path)), unmount_(std::move(unmount)) {}

    ~MountedPartition() { reset(); }

    MountedPartition(MountedPartition&& o) noexcept
        : path_(std::move(o.path_)), unmount_(std::move(o.unmount_)) {
        o.unmount_ = nullptr;
    }

    MountedPartition& operator=(MountedPartition&& o) noexcept {
        if (this != &o) {
            reset();
            path_ = std::move(o.path_);
            unmount_ = std::move(o.unmount_);
            o.unmount_ = nullptr;
        }
        return *this;
    }

    MountedPartition(const MountedPartition&) = delete;
    MountedPartition& operator=(const MountedPartition&) = delete;

    // Filesystem path where the partition is mounted (empty on a default handle).
    const std::string& path() const noexcept { return path_; }

    // True if this handle owns the mount (will unmount on destruction), false
    // for a borrowed / default handle.
    bool owned() const noexcept { return static_cast<bool>(unmount_); }

private:
    void reset() {
        if (unmount_) {
            unmount_();
            unmount_ = nullptr;
        }
    }

    std::string path_;
    std::function<void()> unmount_;  // empty => borrowed (already mounted)
};

}  // namespace kuiper
