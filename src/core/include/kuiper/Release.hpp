#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace kuiper {

// A query for ImageService::listReleases(). `channel` picks the source; `branch`
// and `limit` apply to the unstable (GitHub Actions) channel only.
struct ReleaseQuery {
    std::string channel = "stable";     // "stable" | "unstable"
    std::optional<std::string> branch;  // filter unstable builds to one branch
    int limit = 10;                     // recent successful runs to scan
};

// One fetchable image. Portable: std types only.
//
// `id` is the UNIQUE handle the user passes to `fetch` — for the unstable channel
// it is "gh:<artifactId>". It is deliberately the GitHub artifact id and NOT a
// composed "variant+sha": the same commit is built by more than one successful
// run (re-runs, or push + pull_request on the same SHA), so variant+sha is not
// unique — only the artifact id is. The `gh:` scheme prefix also lets `fetch`
// route to the right provider once the stable channel exists. Humans recognise a
// row via the branch/commit/variant fields; `id` is the copy-paste key.
struct Release {
    std::string id;        // UNIQUE fetch handle, e.g. "gh:9600752484"
    std::string channel;   // "unstable"
    std::string branch;    // "dev_zip" — head branch of the build (unstable)
    std::string commit;    // "829251c" — short head SHA (unstable)
    std::string variant;   // "full" | "basic" — image build type (unstable)
    std::string arch;      // "arm32" | "arm64" — target architecture (unstable)
    std::uint64_t sizeBytes = 0;
    bool available = true;                 // false once the artifact has expired
    std::optional<std::string> expiresAt;  // ISO-8601 (unstable only)
    std::string sourceUri;                 // opaque download URL (the actual bytes)
};

}  // namespace kuiper
