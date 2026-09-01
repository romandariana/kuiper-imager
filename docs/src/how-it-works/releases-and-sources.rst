.. _releases-and-sources:

Releases and Sources
====================

.. description::

   Where images come from: the ReleaseProvider seam, the GitHub Actions
   provider, and the HTTP client's behavior

.. todo::

   Populate. ``list-releases`` enumerates images from one of several sources,
   chosen by channel; ``ImageService`` dispatches to a ``ReleaseProvider``.
   Source: ``plan.md`` §5, ``src/core/include/kuiper/ReleaseProvider.hpp``.

----

The ReleaseProvider Seam
------------------------

.. todo::

   One facade, swappable impls, fake-testable (same shape as
   ``IDriveBackend``). ``list()`` + ``resolve(id) → DownloadSource``. Adding a
   new source is a new provider with no CLI change. Source:
   ``ReleaseProvider.hpp``, ``ImageService.cpp``.

----

Channels: stable and unstable
-----------------------------

.. todo::

   ``stable`` (default) — source still TBD (GitHub Releases? hosted os-list?);
   reports cleanly as not-yet-available. ``unstable`` — GitHub Actions
   artifacts of ``kuiper2_0-build.yml``. Source: ``ImageService.cpp``,
   ``plan.md`` §5, §12.

----

The GitHub Actions Provider
---------------------------

.. todo::

   Lists recent successful runs (branch-filtered server-side), emits one
   ``Release`` per ``*_image`` artifact; ``variantOf`` maps
   ``kuiper_full_64_image`` → {full, arm64}. The identifier is
   ``gh:<artifactId>`` (unique — a commit is built by more than one run, so
   variant+sha collides). Listing needs no auth; ``resolve()`` / download need
   a token; artifacts expire ~90 days. Source: ``src/core/src/image/
   GitHubActionsProvider.{hpp,cpp}``, ``kuiper/Release.hpp``.

----

The HTTP Client
---------------

.. todo::

   libcurl behind ``IHttpClient`` (buffered ``get`` + streaming ``download``).
   Key behaviors: never resend Authorization across a cross-host redirect; no
   overall timeout but a low-speed abort (multi-GB images run for minutes);
   downloads advertise no content encoding so bytes-on-the-wire match the SHA.
   Source: ``src/core/src/http/CurlHttpClient.cpp``.
