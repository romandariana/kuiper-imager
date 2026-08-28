#pragma once

#include <optional>
#include <string>
#include <vector>

#include "kuiper/Error.hpp"
#include "kuiper/Release.hpp"
#include "kuiper/ReleaseProvider.hpp"
#include "kuiper/http/HttpClient.hpp"

namespace kuiper {

// Lists Kuiper 2.0 CI images from the kuiper2_0-build.yml GitHub Actions
// workflow. Scans recent *successful* runs (branch-filtered server-side) and
// emits one Release per "*_image" artifact. Listing needs no auth; a token, if
// supplied, only raises the API rate limit. resolve() turns a "gh:<id>" into the
// artifact's download source (URL + auth headers + canonical filename); the
// download endpoint is auth-gated, so resolve() requires a token.
class GitHubActionsProvider : public ReleaseProvider {
public:
    GitHubActionsProvider(IHttpClient& http, std::optional<std::string> token);

    Result<std::vector<Release>> list(const ReleaseQuery& query) override;
    Result<DownloadSource> resolve(const std::string& id) override;

private:
    // The headers every GitHub API request needs (User-Agent, Accept, API
    // version, and the bearer token when one is set).
    std::vector<HttpHeader> apiHeaders() const;

    // GET a GitHub API URL with apiHeaders(), mapping the HTTP status to a typed
    // Error (401 -> PermissionDenied, 403/429 -> rate-limit hint, ...).
    Result<HttpResponse> apiGet(const std::string& url);

    IHttpClient& http_;
    std::optional<std::string> token_;
};

}  // namespace kuiper
