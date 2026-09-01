.. _core-library:

Core Library (libkuiper)
========================

.. description::

   The UI-agnostic core: the error model, the three services, the drive domain
   model, and the seams that keep it portable

.. todo::

   Populate. ``libkuiper`` links Qt Core only; every operation is a service
   returning a typed result, with progress via a callback. Source:
   ``plan.md`` §5 and the headers under ``src/core/include/kuiper/``.

----

Error Model: Result<T, Error>
-----------------------------

.. todo::

   ``Result<T> = std::expected<T, Error>``; every fallible op returns one (no
   exceptions across the API). Document the ``Error`` struct (code, message,
   details, optional recoverySuggestion) and the ``ErrorCode`` vocabulary
   (NetworkFailure, DiskFull, PermissionDenied, InvalidImage, HashMismatch,
   DeviceRemoved, DeviceBusy, UnsupportedPlatform, NotKuiper2, NotFound,
   UserCancelled, Unknown). Source: ``kuiper/Error.hpp``. Maps to CLI exit
   codes — see :ref:`cli-overview`.

----

The Three Services
------------------

.. todo::

   ``ImageService`` (obtain an image — portable), ``DriveService`` (operate on
   a drive — the platform funnel), ``ConfigurationService`` (configure the
   install — portable, path-based). Cohesion + the funnel invariant. Source:
   ``plan.md`` §5, the service headers.

----

Domain Model: Drive and Partition
---------------------------------

.. todo::

   ``Drive`` owns its ``Partition`` list, filled by one enumeration; the user
   only ever names a whole drive. Nodes are verbatim from the backend, never
   composed by string surgery — this is the fix for the **two-card bug** (udev
   disambiguates colliding labels BOOT/BOOT1 across two cards, so a label can't
   identify a physical card). Source: ``kuiper/Drive.hpp``.

----

Layout Identification
---------------------

.. todo::

   ``identifyLayout()`` classifies partitions into roles by **inspection, not
   index**: boot = vfat (prefer label ≈ BOOT); root = ext4 (prefer label ≈
   rootfs); bootloader = unformatted + unmounted, smallest if several
   (intel-only, optional). Pure and platform-free; returns copies. Source:
   ``kuiper/Layout.hpp``, ``src/core/src/Layout.cpp``.

----

Progress and Cancellation
-------------------------

.. todo::

   ``Progress`` (phase + bytes + fraction + message), ``ProgressFn`` callback,
   ``CancelToken`` (polled between chunks; aborts cleanly leaving the device
   non-bootable, returns UserCancelled). The core never depends on Qt signals.
   Source: ``kuiper/Progress.hpp``.

----

The Seams
---------

.. todo::

   The interfaces that keep the core portable and testable with fakes:
   ``ReleaseProvider`` (per-source image listing — see
   :ref:`releases-and-sources`), ``PreloaderSink`` (the one drive op
   ``ConfigurationService`` needs, injected as a callback), ``IHttpClient``
   (injected HTTP), and the postponed ``ImageReader`` flash seam. Source:
   ``plan.md`` §5, ``kuiper/ReleaseProvider.hpp``, ``kuiper/http/
   HttpClient.hpp``.
