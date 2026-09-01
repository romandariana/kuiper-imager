.. _configure:

Configure: Set Up Boot Files
============================

.. description::

   Scan the boot partition and copy the correct boot files for your eval-board
   and carrier combination

.. todo::

   Populate. Configure is Linux-first and is a C++ port of ADI's
   ``configure-setup.sh``. Source: ``src/cli/main.cpp`` (``cmdListProjects``,
   ``cmdConfigure``), ``src/core/include/kuiper/ConfigurationService.hpp``,
   :ref:`core-library`.

----

list-projects
-------------

.. todo::

   ``kli list-projects --drive <dev>`` scans the card's BOOT partition (mounted
   for you) and lists the available eval-board / carrier / platform / arch
   combinations parsed from the ``*.json`` manifests. Source:
   ``cmdListProjects``, ``ConfigurationService::listProjects``.

----

configure
---------

.. todo::

   ``sudo kli configure --drive <dev> --project <name> --board <carrier>
   [--dry-run] [--force]``. Explain: it copies the kernel + boot files into the
   BOOT root; ``--dry-run`` shows the copy plan without touching the card;
   all-or-nothing preflight (a bad manifest never leaves a half-configured
   card). Source: ``cmdConfigure``, ``ConfigurationService.cpp``.

----

Intel Preloader and extlinux
----------------------------

.. todo::

   Intel projects need a raw preloader write to the (unformatted) bootloader
   partition and boot via ``extlinux/``; ``--force`` allows a non-removable
   bootloader target. The preloader write is wired from the CLI composition
   root to ``DriveService::writePreloader`` via a ``PreloaderSink`` so the
   service stays portable. Source: ``cmdConfigure`` (sink wiring),
   ``ConfigurationService.cpp`` (extlinux handling), :ref:`platform-backends`.
