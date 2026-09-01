.. _installation:

Installation
============

.. description::

   Get Kuiper Imager: build ``kli`` and the GUI from source, or install the
   Debian package

.. todo::

   Populate this page. Kuiper Imager is early development on the ``v2.0``
   branch; today the tool is obtained by building from source (Linux) or from
   the ``.deb``. Sources: ``README.md``, ``CMakePresets.json``,
   ``docker/Dockerfile``, ``plan.md`` §9.

----

Prerequisites
-------------

.. todo::

   List build prerequisites: Qt 6.8+ (LGPLv3 dynamic linking), CMake ≥ 3.22,
   a C++23 compiler (GCC ≥ 12, for real ``std::expected``), plus libarchive,
   OpenSSL (libcrypto), and libcurl. Source: ``plan.md`` §9 (Stack),
   ``docker/Dockerfile``.

----

Build from Source (Docker)
--------------------------

.. todo::

   Document the Docker dev flow (``docker compose build`` / ``run --rm dev``)
   and the CMake presets ``dev`` and ``cli-only``. Source: ``README.md``,
   ``CMakePresets.json``.

----

Build from Source (Native)
--------------------------

.. todo::

   Document the native build (``cmake --preset dev && cmake --build build``)
   and the ``KUIPER_IMAGER_GUI`` toggle for headless/CI builds. Source:
   ``README.md``, ``CMakePresets.json``, ``plan.md`` §3.

----

Debian Package
--------------

.. todo::

   Document the ``.deb`` (built against the distro Qt ≥ 6.4 via the
   ``deb-linux`` preset / CPack DEB) and its runtime dependencies. Source:
   ``plan.md`` §9 (Packaging), ``CMakePresets.json`` (``deb-linux``).
