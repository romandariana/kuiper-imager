Kuiper Imager
=============

.. description::

   Cross-platform tool to fetch, flash, and configure ADI Kuiper Linux images
   for Analog Devices hardware — CLI-first, with a GUI on top

Kuiper Imager is a tool for preparing bootable `ADI Kuiper Linux
<https://github.com/analogdevicesinc/kuiper>`__ SD cards for Analog Devices
hardware. It consolidates a fragmented,
error-prone, multi-tool process into a single application with three core
operations:

**Fetch**
   List official and CI-built Kuiper releases and download the one you want.

**Flash**
   Write an image to an SD card or drive, with progress and read-back
   verification.

**Configure**
   Scan the boot partition and copy the correct boot files for your specific
   eval-board and carrier combination — the most error-prone manual step.

.. todo::

   Landing page. Populate from ``../kuiper-imager_lab/plan.md`` §1 (Goals &
   Scope, "Why v2 exists", guided ``Fetch → Flash → Configure`` workflow) and
   ``README.md``.

----

Status
------

.. todo::

   State what works today: the ``kli`` CLI on **Linux** (``list-drives``,
   ``flash`` of a local image, ``configure``, ``list-releases --unstable``,
   ``fetch``). The GUI lists drives only; Windows/macOS backends and the stable
   release source are postponed. Source: ``plan.md`` header + §11 roadmap.

----

Documentation
=============

.. toctree::
   :maxdepth: 2
   :caption: Getting Started

   getting-started/installation
   getting-started/quick-start

.. toctree::
   :maxdepth: 2
   :caption: Using the CLI

   using-the-cli/cli-overview
   using-the-cli/fetch
   using-the-cli/flash
   using-the-cli/configure

.. toctree::
   :maxdepth: 2
   :caption: How It Works

   how-it-works/architecture
   how-it-works/core-library
   how-it-works/flash-pipeline
   how-it-works/platform-backends
   how-it-works/releases-and-sources

.. toctree::
   :maxdepth: 2
   :caption: Development

   development/development
   development/contributing
   development/roadmap

.. toctree::
   :maxdepth: 2
   :caption: Reference

   reference/troubleshooting
