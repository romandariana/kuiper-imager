.. _fetch:

Fetch: List and Download Releases
=================================

.. description::

   List available Kuiper images and download one with ``list-releases`` and
   ``fetch``

.. todo::

   Populate. Covers the two information/download commands. Source:
   ``src/cli/main.cpp`` (``cmdListReleases``, ``cmdFetch``),
   ``src/core/include/kuiper/ImageService.hpp``, ``plan.md`` §5, §8.

----

list-releases
-------------

.. todo::

   ``kli list-releases [--unstable] [--branch <branch>] [--limit <n>]``.
   Explain the ``stable`` (not yet wired up) vs ``unstable`` (GitHub Actions
   CI builds) channels, the IDENTIFIER column as the copy-paste key for
   ``fetch``, and the branch/commit/variant/arch/expires columns. Source:
   ``cmdListReleases``, ``Release.hpp``, :ref:`releases-and-sources`.

----

fetch
-----

.. todo::

   ``kli fetch --image <id> --output <path> [--force]``. Explain: ``<id>`` is
   an identifier such as ``gh:1234``; ``--output`` may be a file or a directory
   (saved under the artifact's own name); the download is verbatim (no
   decompression); it streams to a ``.part`` file and renames on success, so a
   failed/cancelled fetch never leaves a partial file; refuses to overwrite
   unless ``--force``. Reports bytes written + SHA-256. Source: ``cmdFetch``,
   ``ImageService.cpp`` (fetch pipeline).

----

Tokens, Rate Limits, and Expiry
-------------------------------

.. todo::

   Listing needs no token; downloading a CI artifact is 401-gated (needs
   ``actions:read``). Artifacts expire ~90 days after the run and then list as
   unavailable. Source: ``image/GitHubActionsProvider.cpp``, ``plan.md`` §5,
   :ref:`cli-overview` (Privileges and Tokens).
