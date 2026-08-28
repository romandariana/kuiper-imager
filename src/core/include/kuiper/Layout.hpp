#pragma once

#include <optional>

#include "kuiper/Drive.hpp"
#include "kuiper/Error.hpp"

namespace kuiper {

// The three partitions a Kuiper card can carry, identified by inspection of a
// Drive's enumerated partitions. Each is optional: a freshly flashed card has
// boot + root, RPi / non-intel cards have no bootloader partition, and a blank
// card has none of them.
struct KuiperLayout {
    std::optional<Partition> boot;        // vfat, holds the boot files + manifests
    std::optional<Partition> root;        // ext4 rootfs
    std::optional<Partition> bootloader;  // unformatted partition (intel preloader)
};

// Classify a drive's partitions into Kuiper roles by INSPECTION, never by index.
// This is the fix for the two-card bug: we look at fsType / label / mountpoint
// facts of the very partitions enumerated from the drive the user named, so
// colliding udev labels (BOOT / BOOT1) across two cards can no longer point at
// the wrong medium.
//
// Rules (each independent):
//   boot       : prefer a vfat partition labelled ~"BOOT"; else the first vfat.
//   root       : prefer an ext4 partition labelled ~"rootfs"; else the first ext4.
//   bootloader : unformatted (fsType == "") AND unmounted; if several, the
//                smallest. Optional — most cards have none.
//
// Pure and platform-free: takes copies into the optionals, holds no pointers
// into `drive.partitions`. Errors only if `drive` has no partitions at all
// (a blank card the caller must handle before configuring).
Result<KuiperLayout> identifyLayout(const Drive& drive);

}  // namespace kuiper
