.. _quick-start:

Quick Start
===========

.. description::

   Go from nothing to a bootable Kuiper SD card with the guided
   fetch → flash → configure workflow

.. todo::

   Populate the end-to-end walkthrough. Kuiper Imager suggests a guided
   workflow (these are suggestions, not enforcements)::

      Fetch ─▶ Flash ─▶ Configure ─▶ Bootable SD card
               ▲                       (Raspberry Pi: skip Configure)
         Local image ┘

   Use ``.. shell::`` blocks for each step. Source: ``plan.md`` §1,
   ``src/cli/main.cpp`` (the "Next:" hints printed after each command).

----

1. Fetch an image
-----------------

.. todo::

   ``kli list-releases --unstable`` then ``kli fetch --image <id> --output
   <path>``. See :ref:`fetch`.

----

2. Flash it to a drive
----------------------

.. todo::

   ``kli list-drives`` then ``sudo kli flash --image <file> --drive <dev>``.
   See :ref:`flash`.

----

3. Configure boot files
-----------------------

.. todo::

   ``kli list-projects --drive <dev>`` then ``sudo kli configure --drive <dev>
   --project <name> --board <carrier>``. Raspberry Pi cards skip this step.
   See :ref:`configure`.
