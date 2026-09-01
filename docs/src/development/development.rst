.. _development:

Development
===========

.. description::

   Set up a development environment, understand the project layout, and build
   the CLI, GUI, and packages

.. todo::

   Populate. Development and the Linux build happen in Docker; Windows/macOS
   executables come from native CI runners. Source: ``README.md``,
   ``docker/Dockerfile``, ``docker-compose.yml``, ``CMakePresets.json``.

----

Project Layout
--------------

.. todo::

   ``src/core`` (``libkuiper``), ``src/cli`` (``kli``), ``src/gui``
   (``kuiper-imager``), ``docker/``. Source: ``README.md``.

----

Dev Environment and Presets
---------------------------

.. todo::

   Docker dev shell (``docker compose build`` / ``run --rm dev``); CMake
   presets ``dev`` (Ninja/Debug/GUI on), ``cli-only`` (GUI off),
   ``deb-linux``, and the ``ci-*`` presets; running the GUI over X11
   (``xhost +local:``). Source: ``README.md``, ``CMakePresets.json``.

----

Testing
-------

.. todo::

   ``ctest`` is a TODO (no tests yet); CI smoke test is ``kli version``.
   Source: ``plan.md`` §9 (CI), ``.github/workflows/build.yml``.
