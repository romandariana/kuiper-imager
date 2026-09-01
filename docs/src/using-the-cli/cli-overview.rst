.. _cli-overview:

CLI Overview
============

.. description::

   How the ``kli`` command line works: the whole-drive model, output and exit
   codes, and the privilege and token requirements shared by every command

.. todo::

   Populate the shared CLI conventions. ``kli`` is the scriptability and
   AI-integration surface of Kuiper Imager. Source: ``src/cli/main.cpp``
   (``printUsage``), ``plan.md`` §8.

----

The Whole-Drive Model
---------------------

.. todo::

   One identifier: ``--drive /dev/sda`` is always a whole drive; Kuiper Imager
   finds the BOOT / rootfs / bootloader partitions itself (``identifyLayout``).
   Note that a partition node (``/dev/sda1``) is also accepted and resolves to
   its parent drive. Source: ``src/cli/main.cpp`` (``openBoot``),
   ``plan.md`` §8, :ref:`core-library` (Layout rules).

----

Output Conventions
------------------

.. todo::

   Human-readable output only (no JSON/machine mode). Results → stdout,
   errors/diagnostics/progress → stderr. Source: ``src/cli/main.cpp``
   (``printError``, progress callbacks), ``plan.md`` §8.

----

Exit Codes
----------

.. todo::

   Document the stable exit-code contract so scripts can branch on the failure
   kind: 0 success, 2 usage error, 3 UserCancelled, 4 PermissionDenied,
   5 DeviceBusy, 6 DeviceRemoved, 7 InvalidImage, 8 DiskFull, 9 HashMismatch,
   10 NotFound, 1 otherwise. Source: ``src/cli/main.cpp`` (``exitCodeFor``).
   Render as a ``.. list-table::``.

----

Privileges and Tokens
---------------------

.. todo::

   Flashing and intel preloader writes require root (run with ``sudo``).
   Downloading CI artifacts needs a GitHub token with ``actions:read``;
   discovery order is ``$GH_TOKEN`` → ``$GITHUB_TOKEN`` → ``gh auth token``.
   Listing releases needs no token (only raises the rate limit). Source:
   ``src/cli/main.cpp`` (``printUsage``, ``discoverGitHubToken``),
   :ref:`platform-backends` (privilege model).
