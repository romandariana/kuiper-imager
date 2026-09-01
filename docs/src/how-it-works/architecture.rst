.. _architecture:

Architecture Overview
=====================

.. description::

   The layered design of Kuiper Imager: thin front-ends over a portable core,
   with all platform code behind a single funnel

.. todo::

   Populate. Source: ``../kuiper-imager_lab/plan.md`` §3 (Architecture
   Overview) and §4 (CLI ↔ GUI relation).

----

The Four Layers
---------------

.. todo::

   Front-ends (``kli``, GUI) → core library (``libkuiper``) → platform
   abstraction → external libs. Dependencies point inward only (Clean
   Architecture / Dependency Rule): front-ends depend on the core; the core
   depends on neither front-end. Reproduce the layer diagram from ``plan.md``
   §3.

----

The Funnel Invariant
--------------------

.. todo::

   The key invariant: ``DriveService`` is the *sole* gateway to
   platform-specific code; ``ImageService`` and ``ConfigurationService`` are
   100% portable. Only the platform backend touches syscalls/ioctls/device
   nodes. Source: ``plan.md`` §3, ``src/core/include/kuiper/platform/
   IDriveBackend.hpp``. Detailed in :ref:`platform-backends`.

----

One Core, Two Front-Ends
------------------------

.. todo::

   Both ``kli`` and the GUI link ``libkuiper`` and call it in-process (Option
   A) — so they behave identically by construction, with real-time progress
   (callback) and typed errors. Contrast with Option B (GUI spawns the CLI).
   Build targets: ``kuiper`` (lib), ``kli`` (CLI), ``kuiper-imager`` (GUI); the
   ``KUIPER_IMAGER_GUI`` option drops the GUI for headless/CI builds. Source:
   ``plan.md`` §4, ``README.md``.
