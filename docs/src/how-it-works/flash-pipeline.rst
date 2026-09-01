.. _flash-pipeline:

The Flash Pipeline
==================

.. description::

   How a flash actually runs — the defer-head safety model, O_DIRECT I/O,
   read-back verification, and where the time goes

.. todo::

   Populate. This is the definitive developer reference for the write path.
   Source: ``src/core/src/DriveService.cpp`` (the numbered pipeline),
   ``src/core/src/platform/linux/LinuxDriveBackend.cpp``, ``plan.md`` §7.

----

The Defer-Head Safety Model
---------------------------

.. todo::

   The partition table lives in the first 1 MiB (``kDeferHead``); modern images
   start their first partition at ≥ 1 MiB. Kuiper Imager writes this head
   **last**, after the body is verified, so an interrupted or failed flash
   never leaves a card that looks bootable. Source: ``DriveService.cpp``
   (``kDeferHead``, steps 7–11).

----

The Pipeline, Step by Step
--------------------------

.. todo::

   Walk the numbered steps: guard/re-enumerate → unmount all → exclusive open
   (bounded EBUSY retry) → capacity → wipe signatures → decompress + write body
   (deferring head) → flush → verify body → commit head → flush + re-read part
   table → verify head. Source: ``DriveService.cpp`` ``flash()`` (steps 1–11).

----

O_DIRECT and Verification
-------------------------

.. todo::

   O_DIRECT (buffered fallback on EINVAL) bypasses the page cache so verify
   reads hit the media; alignment is entirely the backend's concern. Dual-hash
   design: ``fullHash`` (reported result) vs ``bodyHash`` (verified before the
   head commit). Source: ``DriveService.cpp`` (``WriteCtx``),
   ``LinuxDriveBackend.cpp`` (AlignedBuf, flushAndSync).

----

Archive and Zip Handling
------------------------

.. todo::

   Accepted filters (gzip/xz/zstd/bzip2) and formats (raw + zip); why
   ``support_format_all`` is avoided; the zip entry-selection rule (largest
   regular file; refuse when ambiguous). Source: ``DriveService.cpp``
   (``looksLikeZip``, ``chooseZipEntry``).

----

Performance and Timings
-----------------------

.. todo::

   SHA-256 via OpenSSL EVP uses hardware SHA extensions (~15× faster than Qt's
   software hash). The ``--timings`` breakdown (``FlashTimings``) exposes
   decompress-vs-deviceWrite and deviceWrite-vs-flush. Source:
   ``src/core/src/util/Sha256.hpp``, ``DriveService.hpp`` (``FlashTimings``),
   ``src/cli/main.cpp`` (``printTimings``).
