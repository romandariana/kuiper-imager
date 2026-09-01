.. _flash:

Flash: Write an Image to a Drive
================================

.. description::

   Write a local image to an SD card or drive with progress and read-back
   verification

.. todo::

   Populate. Source: ``src/cli/main.cpp`` (``cmdFlash``),
   ``src/core/include/kuiper/DriveService.hpp``, ``plan.md`` §7.

----

The flash command
-----------------

.. todo::

   ``sudo kli flash --image <file> --drive <dev> [--yes] [--force]
   [--no-verify] [--timings]``. The image may be raw ``.img`` or
   ``.zip/.xz/.zst/.gz/.bz2`` (decompressed inline). A loud confirmation
   prompt guards the erase unless ``--yes``. Source: ``cmdFlash``.

----

Options
-------

.. todo::

   Document each flag: ``--yes`` (skip prompt); ``--force`` (allow
   non-removable drives, e.g. ``/dev/loopN`` — used with care); ``--no-verify``
   (skip the read-back verify, ~half the wall time; the partition table is
   still written last and checked); ``--timings`` (per-phase breakdown).
   Source: ``cmdFlash``, ``DriveService.hpp`` (``WriteOptions``,
   ``FlashTimings``). Render options as a ``.. list-table::``.

----

Verification and Safety
-----------------------

.. todo::

   Read-back SHA-256 verification is the integrity guarantee that distinguishes
   Kuiper Imager from a raw ``dd``, and the partition-table head is always
   written last so a failed or skipped-verify flash never leaves a
   bootable-looking card. Full mechanics live in :ref:`flash-pipeline`.
   Source: ``DriveService.hpp`` (``WriteOptions::verify``).
