.. _platform-backends:

Platform Backends and Privilege
===============================

.. description::

   The single platform seam, the Linux backend's device I/O, the privilege
   model, and the planned Windows and macOS backends

.. todo::

   Populate. Raw device access and privilege elevation differ fundamentally per
   OS; this is exactly what ``DriveService`` funnels. Source:
   ``src/core/include/kuiper/platform/IDriveBackend.hpp``, ``plan.md`` §6.

----

The IDriveBackend Funnel
------------------------

.. todo::

   One interface, one impl compiled per OS (``makeDriveBackend()`` factory).
   Only the backend touches syscalls/ioctls/device nodes; short-write/read/
   EINTR loops and O_DIRECT block alignment are handled internally so callers
   pass arbitrary offsets/lengths. Source: ``IDriveBackend.hpp``.

----

The Linux Backend
-----------------

.. todo::

   ``lsblk -b -J -p`` enumeration (whole disks only; loop/ram/zram/sr dropped;
   top-level partitions only, so no LVM/LUKS/RAID); O_DIRECT raw I/O with
   4 MiB aligned staging; the udev auto-remount race (O_EXCL + bounded EBUSY
   retry → unmountAll); wipe ranges (4 MiB head, 1 MiB tail); dropping the page
   cache before verify. Source: ``src/core/src/platform/linux/
   LinuxDriveBackend.cpp``.

----

The Privilege Model
-------------------

.. todo::

   The CLI runs as root via ``sudo``: only four ops truly need root (device
   open, umount2/swapoff, BLKRRPART, BLKFLSBUF). Explain why not udisks2
   (desktop-shaped, poor fit for CLI/SSH/CI) and the planned GUI direction (a
   small privileged helper). Errno → error mapping surfaces EACCES/EPERM as
   PermissionDenied ("run with sudo"). Source: ``plan.md`` §6,
   ``LinuxDriveBackend.cpp`` (``ioError``).

----

Windows and macOS (Planned)
---------------------------

.. todo::

   Both backends are compilable stubs returning UnsupportedPlatform (Phase 4).
   Windows: SetupAPI enumeration + ``CreateFile`` on ``\\.\PhysicalDriveN``
   under UAC. macOS: DiskArbitration/IOKit + ``/dev/rdiskN`` with an fd from
   ``authopen`` over SCM_RIGHTS. Source: ``platform/windows/
   WindowsDriveBackend.cpp``, ``platform/macos/MacOSDriveBackend.cpp``,
   ``plan.md`` §6.
