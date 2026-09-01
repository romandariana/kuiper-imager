.. _troubleshooting:

Troubleshooting
===============

.. description::

   Common problems and what they mean, mapped to Kuiper Imager's error codes

.. todo::

   Populate. Group by the error the user actually sees; each maps to an
   ``ErrorCode`` / exit code (see :ref:`cli-overview`). Sources:
   ``src/cli/main.cpp`` (``printError``, ``exitCodeFor``),
   ``src/core/src/platform/linux/LinuxDriveBackend.cpp`` (``ioError``).

----

Permission Denied
-----------------

.. todo::

   Raw device access needs root: run flash / configure with ``sudo``. Exit
   code 4 (PermissionDenied). Source: ``ioError`` (EACCES/EPERM).

----

Device Busy
-----------

.. todo::

   A live mount / swap / md / LVM / LUKS holder blocks the write. Exit code 5
   (DeviceBusy). Source: ``LinuxDriveBackend.cpp`` (``unmountAll``, O_EXCL).

----

Drive Not Found or Not a Kuiper Card
------------------------------------

.. todo::

   ``--drive`` must be a whole drive from ``kli list-drives`` (exit code 10,
   NotFound); a card with no BOOT partition is not a flashed Kuiper card (exit
   code, NotKuiper2). Source: ``src/cli/main.cpp`` (``openBoot``).

----

Fetch Fails with 401 / Token Errors
-----------------------------------

.. todo::

   Downloading CI artifacts needs a GitHub token with ``actions:read``; set
   ``$GH_TOKEN``/``$GITHUB_TOKEN`` or log in with ``gh``. See
   :ref:`fetch` and :ref:`cli-overview`. Source: ``GitHubActionsProvider.cpp``.

----

Hash Mismatch
-------------

.. todo::

   The read-back verify found the media doesn't match what was written (exit
   code 9, HashMismatch); the partition table is left wiped so the card isn't
   bootable. Source: ``DriveService.cpp`` (verify steps).

----

The GUI Only Lists Drives
-------------------------

.. todo::

   The GUI is an early skeleton: it lists drives only. Use ``kli`` for flash /
   fetch / configure. Source: ``src/gui/MainWindow.cpp``, :ref:`roadmap`.
