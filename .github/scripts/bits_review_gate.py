# Copyright 2026, Datadog, Inc.
"""GitHub API layer and CLI for the Bits review merge gate.

``GitHubClient`` reads pull requests, PR reviews and commit statuses
through an injectable transport (the stdlib ``urllib.request`` by
default). Every read fails closed through :class:`ApiError`: transport
failures, non-2xx after retries, GraphQL ``errors`` (even with partial
data), malformed JSON and missing response structure never yield a
partial list. Reads carry ``GITHUB_TOKEN`` only; ``STATUS_TOKEN`` is
never read here.

On top of the client, ``normalize_review`` maps GraphQL review nodes to
the policy's record shape and ``read_sha_snapshot`` wires the policy
validators into the fetch path, recording api-error and invalid-input
flags instead of skipping or truncating malformed input.
``revalidated_decision`` composes the decision on that seam: it
reads a snapshot, computes the decision with the policy, then re-reads
the snapshot and compares full decision-input fingerprints until they
match — return values only: no status is read or written there. The
``publish --sha H``
subcommand consumes the seam's decision: it suppresses the write when
the newest ``bits-review/head`` status created by ``dd-octo-sts[bot]``
already equals the decision, else POSTs it with ``STATUS_TOKEN`` only;
an unchanged or published ``error`` decision still exits 1. The
``resolve`` subcommand turns event selectors, received only through
environment
variables, into the deduplicated head-SHA list to publish; it never
interpolates event text into a command and executes nothing.
"""

import argparse
import json
import os
import re
import sys
import time
import urllib.error
import urllib.parse
import urllib.request

import bits_review_gate_policy as policy

#: Total attempts for network errors, 5xx responses and rate-limited
#: 403/429 responses; every other 4xx gets one.
MAX_ATTEMPTS = 3
_RETRY_BACKOFF_SECONDS = 0.2
_TIMEOUT_SECONDS = 30
REST_PER_PAGE = 100
REVIEW_PAGE_SIZE = 100
#: Distinct head SHAs one resolve run may emit; more is an error, never a
#: truncation.
MAX_RESOLVE_SHAS = 256
#: Pages one paginated read (GraphQL reviews, REST lists) may follow; more
#: is an error, never a truncation.
MAX_FETCH_PAGES = 20
#: Unstable fingerprint comparisons one decision may survive; after the
#: third nothing is written — a still-changing review set is not a
#: publishable state.
MAX_UNSTABLE_COMPARISONS = 3
#: Upper bound for honoring a server-provided rate-limit window
#: (Retry-After, else x-ratelimit-reset), so a primary limit cannot stall
#: the workflow run.
_MAX_RETRY_AFTER_SECONDS = 300
_SHA_RE = re.compile(r"[0-9a-f]{40}")
_DEFAULT_API_URL = "https://api.github.com"
_DEFAULT_GRAPHQL_URL = "https://api.github.com/graphql"
#: The app login whose statuses are this gate's own output; only its
#: entries are candidates for unchanged-status suppression.
STATUS_CREATOR = "dd-octo-sts[bot]"

#: The contract's review query: identity, state, body, timestamps, the
#: head commit and author typing. No edit-history field is requested.
_REVIEWS_QUERY = """query($owner: String!, $name: String!, $number: Int!, $after: String) {
  repository(owner: $owner, name: $name) {
    pullRequest(number: $number) {
      reviews(first: %d, after: $after) {
        pageInfo { hasNextPage endCursor }
        nodes {
          databaseId
          state
          body
          submittedAt
          lastEditedAt
          commit { oid }
          author {
            __typename
            login
            ... on Bot { databaseId }
            ... on User { databaseId }
          }
        }
      }
    }
  }
}
""" % REVIEW_PAGE_SIZE


class ApiError(Exception):
    """The fail-closed signal every failed or malformed API read raises."""


class RateLimitError(ApiError):
    """An API read that failed because the rate-limit window exceeds what
    honoring retries can cover."""


class ResolveError(Exception):
    """Invalid resolve input, or a result the resolver refuses to truncate."""


def _urllib_transport(request):
    """The default transport: one stdlib urllib call per request, with
    redirects refused — the redirect handler would forward the
    Authorization header (the status token on the POST) to any target."""
    return _NO_REDIRECT_OPENER.open(request, timeout=_TIMEOUT_SECONDS)


class _NoRedirect(urllib.request.HTTPRedirectHandler):
    """Refuses every redirect: ``redirect_request`` returning None makes
    urllib surface the 3xx as an HTTPError, which _fetch fails closed on."""

    def redirect_request(self, req, fp, code, msg, headers, newurl):
        return None


_NO_REDIRECT_OPENER = urllib.request.build_opener(_NoRedirect)


def _next_link(link_header, base_url):
    """The rel="next" URL of a Link header constrained to the API origin
    (same scheme and host), or None on the last page."""
    if not link_header:
        return None
    base = urllib.parse.urlsplit(base_url)
    for next_url in re.findall(r'<([^>]*)>\s*;\s*rel="next"', link_header):
        if not next_url:
            continue
        parts = urllib.parse.urlsplit(next_url)
        if (parts.scheme.lower(), parts.netloc.lower()) != (base.scheme.lower(), base.netloc.lower()):
            raise ApiError("cross-origin next-page URL: %r" % (next_url,))
        return next_url
    return None


def _header_lookup(headers, name):
    """The value of one header matched case-insensitively, or None:
    urllib exposes ``email.message.Message`` while test fakes may carry
    plain case-sensitive dicts."""
    if not headers:
        return None
    lowered = name.lower()
    for key, value in headers.items():
        if key.lower() == lowered:
            return value
    return None


def _is_rate_limited(status, headers):
    """True for a 403/429 GitHub rate-limit response.

    A 429 is rate-limited only when a Retry-After header is present —
    remaining 0 alone never retries it. A 403 is rate-limited only when
    ``x-ratelimit-remaining`` is 0; a plain 403 is never retried, with
    or without Retry-After.
    """
    if status not in (403, 429):
        return False
    remaining = _header_lookup(headers, "x-ratelimit-remaining")
    if status == 403:
        return remaining is not None and str(remaining).strip() == "0"
    return _header_lookup(headers, "Retry-After") is not None


def _retry_after_seconds(headers):
    """The integer-seconds Retry-After delay of the headers, or None when
    absent or unparseable (HTTP-date form is never parsed). The delay is
    never negative: a hostile value clamps to zero."""
    value = _header_lookup(headers, "Retry-After")
    if value is None:
        return None
    try:
        return max(0, int(str(value).strip()))
    except ValueError:
        return None


def _rate_limit_window_seconds(headers):
    """The rate-limit window the headers advertise, in seconds, or None
    when neither signal parses: the Retry-After delay if present (already
    non-negative), else the seconds until the ``x-ratelimit-reset`` epoch,
    clamped to zero. An HTTP-date Retry-After is never parsed, so it
    falls through to the reset reading."""
    retry_after = _retry_after_seconds(headers)
    if retry_after is not None:
        return retry_after
    reset = _header_lookup(headers, "x-ratelimit-reset")
    if reset is None:
        return None
    try:
        return max(0, int(str(reset).strip()) - time.time())
    except ValueError:
        return None


def _close_quietly(response):
    """Close one response-like object, tolerating one without ``close``."""
    close = getattr(response, "close", None)
    if close is not None:
        close()


class GitHubClient:
    """Reads the gate's decision inputs from the GitHub API.

    ``transport`` is a callable taking a ``urllib.request.Request`` and
    returning an HTTP-response-like object (``status``, ``read()``,
    ``headers``). ``env`` supplies ``GITHUB_API_URL``,
    ``GITHUB_GRAPHQL_URL`` and ``GITHUB_TOKEN``; ``repo`` is the
    ``owner/name`` repository.
    """

    def __init__(self, repo, transport=None, env=None):
        self._repo = repo
        self._transport = _urllib_transport if transport is None else transport
        env = os.environ if env is None else env
        self._api_url = env.get("GITHUB_API_URL", _DEFAULT_API_URL).rstrip("/")
        self._graphql_url = env.get("GITHUB_GRAPHQL_URL", _DEFAULT_GRAPHQL_URL)
        self._token = env.get("GITHUB_TOKEN")

    @property
    def repo(self):
        """The ``owner/name`` repository every request addresses."""
        return self._repo

    def list_open_main_prs(self):
        """Every open PR based on ``main``, all pages, drafts included."""
        url = "%s/repos/%s/pulls?state=open&base=main&per_page=%d" % (
            self._api_url, self._repo, REST_PER_PAGE)
        return self._fetch_json_pages(url)

    def get_pr(self, number):
        """One PR record by number, whatever its state or base — the live
        head source for pull_request_target events."""
        if not _is_positive_int(number):
            raise ApiError("invalid PR number: %r" % (number,))
        url = "%s/repos/%s/pulls/%d" % (self._api_url, self._repo, number)
        body, _ = self._fetch(url)
        try:
            record = json.loads(body)
        except ValueError as error:
            raise ApiError("malformed JSON from %s" % (url,)) from error
        if not isinstance(record, dict):
            raise ApiError("expected a JSON object from %s" % (url,))
        return record

    def read_statuses(self, sha):
        """Every commit status recorded for ``sha``, all pages."""
        url = "%s/repos/%s/commits/%s/statuses?per_page=%d" % (
            self._api_url, self._repo, sha, REST_PER_PAGE)
        return self._fetch_json_pages(url)

    def create_status(self, sha, status, token):
        """POST one commit status for ``sha`` with ``token`` — the status
        token only; the read token never publishes. The write targets
        exactly the ``sha`` the caller validated, never any other head."""
        url = "%s/repos/%s/statuses/%s" % (self._api_url, self._repo, sha)
        if not token:
            raise ApiError("no STATUS_TOKEN for %s" % (url,))
        self._fetch(url, payload=status, token=token)

    def fetch_reviews(self, pr):
        """Every review node of PR ``pr`` (a number or a record with a
        ``number`` member), following ``pageInfo.hasNextPage``."""
        nodes = []
        cursor = None
        pages = 0
        while True:
            page_nodes, page_info = self._fetch_reviews_page(pr, cursor)
            nodes.extend(page_nodes)
            if not page_info["hasNextPage"]:
                return nodes
            pages += 1
            if pages >= MAX_FETCH_PAGES:
                raise ApiError("reviews pagination for %r exceeds %d pages"
                               % (pr, MAX_FETCH_PAGES))
            cursor = page_info["endCursor"]
            if not isinstance(cursor, str):
                raise ApiError("reviews page for %r carries no endCursor" % (pr,))

    def _fetch_reviews_page(self, pr, cursor):
        number = pr.get("number") if isinstance(pr, dict) else pr
        if not isinstance(number, int) or isinstance(number, bool) or number <= 0:
            raise ApiError("invalid PR number: %r" % (number,))
        owner, sep, name = self._repo.partition("/")
        if not (owner and sep and name):
            raise ApiError("invalid repository: %r" % (self._repo,))
        payload = {
            "query": _REVIEWS_QUERY,
            "variables": {"owner": owner, "name": name, "number": number, "after": cursor},
        }
        body, _ = self._fetch(self._graphql_url, payload=payload)
        try:
            document = json.loads(body)
        except ValueError as error:
            raise ApiError("malformed GraphQL response for PR %s" % (number,)) from error
        if not isinstance(document, dict):
            raise ApiError("malformed GraphQL response for PR %s" % (number,))
        if document.get("errors"):
            raise ApiError("GraphQL errors for PR %s: %r" % (number, document.get("errors")))
        reviews = document
        for key in ("data", "repository", "pullRequest", "reviews"):
            if not isinstance(reviews, dict) or not isinstance(reviews.get(key), dict):
                raise ApiError("GraphQL response for PR %s misses %s" % (number, key))
            reviews = reviews[key]
        page_info = reviews.get("pageInfo")
        page_nodes = reviews.get("nodes")
        if (not isinstance(page_info, dict)
                or not isinstance(page_info.get("hasNextPage"), bool)
                or not isinstance(page_nodes, list)):
            raise ApiError("GraphQL reviews for PR %s miss nodes or pageInfo" % (number,))
        return page_nodes, page_info

    def _build_request(self, url, payload, token=None):
        """One request. ``token`` overrides the read token — only the
        status write passes it (STATUS_TOKEN); reads stay on GITHUB_TOKEN."""
        headers = {"Accept": "application/vnd.github+json"}
        auth = self._token if token is None else token
        if auth:
            headers["Authorization"] = "Bearer " + auth
        data = None
        method = "GET"
        if payload is not None:
            data = json.dumps(payload).encode("utf-8")
            headers["Content-Type"] = "application/json"
            method = "POST"
        return urllib.request.Request(url, data=data, headers=headers, method=method)

    def _fetch(self, url, payload=None, token=None):
        """One request with retries. Network errors, 5xx responses and
        rate-limited responses get up to MAX_ATTEMPTS attempts (a 429
        needs a Retry-After header to count as rate-limited; a 403 needs
        ``x-ratelimit-remaining`` 0); every other 4xx exactly one. A
        rate-limit window beyond the honor cap fails fast instead of
        retrying. Returns (body_bytes, link_header)."""
        failure = None
        for attempt in range(1, MAX_ATTEMPTS + 1):
            request = self._build_request(url, payload, token)
            window = None
            # The flag names the last attempt's classification: a mixed
            # retry sequence must never report a rate limit its final
            # failure did not have.
            rate_limited_last = False
            status = None
            headers = {}
            try:
                response = self._transport(request)
                try:
                    status = response.status
                    headers = getattr(response, "headers", None) or {}
                    body = response.read()
                finally:
                    _close_quietly(response)
            except urllib.error.HTTPError as error:
                _close_quietly(error)
                if error.code < 500 and not _is_rate_limited(error.code, error.headers):
                    raise ApiError("HTTP %s for %s" % (error.code, url)) from error
                failure = error
                if _is_rate_limited(error.code, error.headers):
                    rate_limited_last = True
                    window = _rate_limit_window_seconds(error.headers)
            except Exception as error:  # any transport failure retries
                if (status is not None
                        and not (200 <= status < 300 or status >= 500
                                 or _is_rate_limited(status, headers))):
                    # The status was already read as a non-retryable
                    # non-2xx; retrying a failed body read of it would
                    # break the one-attempt contract.
                    raise ApiError("HTTP %s for %s" % (status, url)) from error
                failure = error
                if status is not None and _is_rate_limited(status, headers):
                    rate_limited_last = True
                    window = _rate_limit_window_seconds(headers)
            else:
                if 200 <= status < 300:
                    return body, headers.get("Link")
                failure = ApiError("HTTP %s for %s" % (status, url))
                if status < 500 and not _is_rate_limited(status, headers):
                    break
                if _is_rate_limited(status, headers):
                    rate_limited_last = True
                    window = _rate_limit_window_seconds(headers)
            if attempt < MAX_ATTEMPTS:
                if window is not None and window > _MAX_RETRY_AFTER_SECONDS:
                    raise RateLimitError(
                        "rate limit for %s: window %d s exceeds the %d s honor cap"
                        % (url, int(window), _MAX_RETRY_AFTER_SECONDS)) from failure
                if window is not None:
                    time.sleep(min(window, _MAX_RETRY_AFTER_SECONDS))
                else:
                    time.sleep(_RETRY_BACKOFF_SECONDS * attempt)
        if rate_limited_last:
            raise RateLimitError("rate limit for %s after %d attempts"
                                 % (url, MAX_ATTEMPTS)) from failure
        if isinstance(failure, ApiError):
            raise failure
        raise ApiError("transport failure for %s" % (url,)) from failure

    def _fetch_json_pages(self, url):
        """Every page of a REST list endpoint, following the Link header's
        rel="next" URL until a page reports none. More than
        MAX_FETCH_PAGES pages fails the whole read."""
        items = []
        start_url = url
        pages = 0
        while url is not None:
            body, link = self._fetch(url)
            try:
                page = json.loads(body)
            except ValueError as error:
                raise ApiError("malformed JSON from %s" % (url,)) from error
            if not isinstance(page, list):
                raise ApiError("expected a JSON array from %s" % (url,))
            items.extend(page)
            url = _next_link(link, self._api_url)
            pages += 1
            if url is not None and pages >= MAX_FETCH_PAGES:
                raise ApiError("REST pagination from %s exceeds %d pages"
                               % (start_url, MAX_FETCH_PAGES))
        return items


def normalize_review(node):
    """Map one GraphQL review node to the contract's normalized record.

    Every value is carried raw — ``lastEditedAt`` keeps its exact value,
    never a boolean — and a null author maps to a null ``author_typename``.
    Bot identity comes only from ``author.__typename`` and
    ``author.databaseId``; REST-named fields are never consulted. A node
    that is not a JSON object maps to an empty record, which the policy
    validators report as invalid input rather than skipping it.
    """
    if not isinstance(node, dict):
        node = {}
    author = node.get("author")
    if not isinstance(author, dict):
        author = {}
    commit = node.get("commit")
    return {
        "id": node.get("databaseId"),
        "author_typename": author.get("__typename"),
        "author_id": author.get("databaseId"),
        "author_login": author.get("login"),
        "state": node.get("state"),
        "body": node.get("body"),
        "commit_oid": commit.get("oid") if isinstance(commit, dict) else None,
        "submitted_at": node.get("submittedAt"),
        "last_edited_at": node.get("lastEditedAt"),
    }


def read_sha_snapshot(sha, client):
    """Read snapshot S(i) for one head SHA through the validated seam.

    Returns ``{"sha", "api_error", "invalid_input", "prs", "reviews",
    "outcomes"}``: ``prs`` holds the validated P(H) members (open ``main``
    PRs whose head SHA equals ``sha``), ``reviews`` maps each member's
    number to its normalized records and ``outcomes`` to its policy
    outcome, and the two flag lists carry every api-error/invalid-input
    location (``"pulls"``, ``"pr-<n>/reviews"``, ``"pr-record:<field>"`,
    ``"pr-<n>"``). Failures and malformed inputs are flagged, never
    skipped or truncated: a malformed PR record cannot be scoped, so it
    flags the snapshot invalid-input instead of letting a shrunk P(H)
    reveal a PASS.
    """
    snapshot = {
        "sha": sha,
        "api_error": [],
        "invalid_input": [],
        "prs": [],
        "reviews": {},
        "outcomes": {},
    }
    try:
        open_prs = client.list_open_main_prs()
    except RateLimitError:
        snapshot["api_error"].append("pulls:rate-limit")
        return snapshot
    except ApiError:
        snapshot["api_error"].append("pulls")
        return snapshot
    for pr in open_prs:
        if not isinstance(pr, dict):
            snapshot["invalid_input"].append("pr-record:record")
            continue
        field = policy.validate_pr_record(pr)
        if field is not None:
            snapshot["invalid_input"].append("pr-record:" + field)
            continue
        if pr["head"]["sha"] != sha:
            continue
        number = pr["number"]
        snapshot["prs"].append(pr)
        try:
            records = [normalize_review(node) for node in client.fetch_reviews(pr)]
        except RateLimitError:
            snapshot["api_error"].append("pr-%d/reviews:rate-limit" % (number,))
            snapshot["outcomes"][number] = "api-error"
            continue
        except ApiError:
            snapshot["api_error"].append("pr-%d/reviews" % (number,))
            snapshot["outcomes"][number] = "api-error"
            continue
        snapshot["reviews"][number] = records
        result = policy.outcome(records, head=sha)
        snapshot["outcomes"][number] = result
        if result == "invalid-input":
            snapshot["invalid_input"].append("pr-%d" % (number,))
    return snapshot


def _decision_payload(snapshot, repo):
    """The decision D(i) of one validated snapshot, as the status payload
    the publisher will carry: state, reason, governing PR, description,
    target URL and context.

    api-error and invalid-input flags propagate as error decisions. A
    member PR's flags already carry its own outcome; the snapshot-level
    locations — a failed pulls read (``pulls``) or a malformed PR record
    (``pr-record:<field>``) — name no PR, so they force the error state on
    their own, even when every scoped member evaluated cleanly. A
    snapshot-level error with no member names no PR at all:
    ``policy.describe`` and ``policy.target_url`` require an API PR
    number, none exists, so description and target URL stay None.

    Returns None when P(H) was read successfully and is empty: no PR
    shares the head, so no decision exists and nothing may publish.
    """
    outcomes = snapshot["outcomes"]
    base = policy.decide(outcomes) if outcomes else None
    level_api_flags = [flag for flag in snapshot["api_error"] if flag.startswith("pulls")]
    level_invalid_flags = [flag for flag in snapshot["invalid_input"]
                           if str(flag).startswith("pr-record:")]
    level_flags = level_api_flags + level_invalid_flags
    if base is None and not level_flags:
        return None
    if level_flags:
        # A snapshot-level flag names no PR; it forces error even when
        # every scoped member evaluated cleanly. The reason names the
        # class that forced the level; a failed pulls read outranks a
        # malformed record when both are present.
        reason = "api-error" if level_api_flags else "invalid-input"
        governing_pr = base["governing_pr"] if base is not None else None
    else:
        reason = base["reason"]
        governing_pr = base["governing_pr"]
    state = "error" if level_flags else base["state"]
    detail = None
    if state == "error":
        flags = snapshot["api_error"] if reason == "api-error" else snapshot["invalid_input"]
        detail = ", ".join(sorted(str(flag) for flag in flags)) or None
    description = None
    review_id = None
    target_url = None
    if governing_pr is not None:
        description = policy.describe(reason, governing_pr, detail)
        # missing, api-error and invalid-input have no governing review:
        # an error names no single review, missing means none exists.
        if reason not in ("missing", "api-error", "invalid-input"):
            latest = policy.latest_candidate(
                snapshot["reviews"].get(governing_pr, []), head=snapshot["sha"])
            review_id = latest.get("id") if latest is not None else None
        target_url = policy.target_url(repo, governing_pr, review_id)
    return {
        "state": state,
        "reason": reason,
        "governing_pr": governing_pr,
        "description": description,
        "target_url": target_url,
        "context": policy.STATUS_CONTEXT,
    }


def revalidated_decision(sha, client):
    """The validated decision for one head SHA: the contract's snapshot
    algorithm minus the write step.

    Reads S(i) through ``read_sha_snapshot`` (P(H) plus the normalized
    reviews and error flags), computes D(i) with the policy, then reads
    S(i+1) and compares ``policy.fingerprint`` over every decision
    input. A mismatch discards D(i) — the loop restarts from the new
    snapshot — and after ``MAX_UNSTABLE_COMPARISONS`` consecutive
    mismatches returns ``("unstable", None)``: nothing may be
    published. Return values only, no side effects: no status is read
    or written here — ``_publish_status`` does that on the returned
    decision.

    - ``("empty", None)`` — P(H) was read successfully and is empty;
      no second snapshot is read.
    - ``("stable", D)`` — D is the decision of the revalidated
      snapshot.
    - ``("unstable", None)`` — the snapshot kept changing under the
      reads.
    """
    snapshot = read_sha_snapshot(sha, client)
    for _ in range(MAX_UNSTABLE_COMPARISONS):
        decision = _decision_payload(snapshot, client.repo)
        if decision is None:
            return ("empty", None)
        expected = policy.fingerprint(snapshot)
        confirmed = read_sha_snapshot(sha, client)
        if policy.fingerprint(confirmed) == expected:
            return ("stable", decision)
        snapshot = confirmed
    return ("unstable", None)


def _selected_app_status(statuses):
    """The ``bits-review/head`` status created by the gate's publisher
    app with the greatest (created_at, id), or None when none exists.

    Statuses from any other creator are never selected — they are not
    this gate's output and must not satisfy its comparison. A record
    without a string ``created_at`` or a positive-int ``id`` cannot be
    ordered, so it is never selected: a malformed entry cannot suppress
    a needed write. GitHub ``created_at`` values are uniform UTC
    ISO-8601 strings, where lexicographic order equals chronological
    order.
    """
    selected = None
    selected_key = None
    for status in statuses:
        if not isinstance(status, dict) or status.get("context") != policy.STATUS_CONTEXT:
            continue
        creator = status.get("creator")
        if not isinstance(creator, dict) or creator.get("login") != STATUS_CREATOR:
            continue
        created = status.get("created_at")
        status_id = status.get("id")
        if not isinstance(created, str) or not _is_positive_int(status_id):
            continue
        key = (created, status_id)
        if selected_key is None or key > selected_key:
            selected = status
            selected_key = key
    return selected


def _matches_decision(status, decision):
    """True when the stored status equals the decision in every field
    the write would carry: state, description, target URL and context."""
    return (status.get("state") == decision["state"]
            and status.get("description") == decision["description"]
            and status.get("target_url") == decision["target_url"]
            and status.get("context") == decision["context"])


def _status_payload(decision):
    """The POST body: state and context always, the optional fields only
    when the decision carries them — a member-less error names neither a
    PR number nor a review, so it omits both rather than inventing
    values."""
    payload = {"state": decision["state"], "context": decision["context"]}
    if decision["description"] is not None:
        payload["description"] = decision["description"]
    if decision["target_url"] is not None:
        payload["target_url"] = decision["target_url"]
    return payload


def _publish_status(sha, client, status_token):
    """Publish the validated decision for one head SHA and return the
    process exit code.

    The seam's ``empty`` return exits 0 without a write and its
    ``unstable`` return exits 1 without a write — a still-changing
    review set is never published. For a stable decision the latest app
    status is
    selected and compared: an exact match skips the POST (exit 0 for a
    non-error decision — an ``error`` decision still exits 1 even though
    its POST is suppressed), and a failed status read never suppresses
    the write. A published non-error decision exits 0; a published
    ``error`` decision and any failed write exit 1. Success — a POST
    carrying ``state: success`` and exit 0 — can only ever come from the
    all-pass conjunction branch.
    """
    kind, decision = revalidated_decision(sha, client)
    if kind == "empty":
        return 0
    if kind == "unstable":
        return 1
    try:
        statuses = client.read_statuses(sha)
    except ApiError:
        statuses = None  # a failed read never suppresses a safety update
    if statuses is not None:
        current = _selected_app_status(statuses)
        if current is not None and _matches_decision(current, decision):
            return 1 if decision["state"] == "error" else 0
    try:
        client.create_status(sha, _status_payload(decision), status_token)
    except ApiError:
        return 1
    return 1 if decision["state"] == "error" else 0


def _is_positive_int(value):
    """True for a genuine positive int; bool is an int subclass and excluded."""
    return isinstance(value, int) and not isinstance(value, bool) and value > 0


def _env_int(env, name):
    """The positive-int value of one env entry; anything else is invalid
    input. Env values arrive as strings; genuine ints are accepted for
    in-process callers."""
    value = env.get(name)
    if _is_positive_int(value):
        return value
    try:
        number = int(str(value))
    except (TypeError, ValueError):
        number = None
    if not _is_positive_int(number):
        raise ResolveError("invalid %s: %r" % (name, value))
    return number


def _env_sha(env, name):
    value = env.get(name)
    if not isinstance(value, str) or _SHA_RE.fullmatch(value) is None:
        raise ResolveError("invalid %s: %r" % (name, value))
    return value


def _env_str(env, name):
    value = env.get(name)
    if not isinstance(value, str) or not value:
        raise ResolveError("invalid %s: %r" % (name, value))
    return value


def _env_pr_numbers(env, name):
    """The JSON list of PR numbers; null members (GitHub's ``toJSON([*])``
    padding) are dropped, every other member must be a positive int."""
    raw = env.get(name)
    try:
        numbers = json.loads(raw) if isinstance(raw, str) else None
    except ValueError:
        numbers = None
    if not isinstance(numbers, list):
        raise ResolveError("invalid %s: %r" % (name, raw))
    numbers = [n for n in numbers if n is not None]
    if not all(_is_positive_int(n) for n in numbers):
        raise ResolveError("invalid %s: %r" % (name, raw))
    return numbers


def _pr_selector(pr):
    """(head repository full name, head branch) of a PR record, or None
    when either member is missing or not a string. Selector values are used
    only in comparisons, never in commands or URLs."""
    head = pr.get("head") if isinstance(pr, dict) else None
    if not isinstance(head, dict):
        return None
    repo = head.get("repo")
    full_name = repo.get("full_name") if isinstance(repo, dict) else None
    branch = head.get("ref")
    if not (isinstance(full_name, str) and isinstance(branch, str)):
        return None
    return (full_name, branch)


def _require_pr_record(pr):
    record = pr if isinstance(pr, dict) else {}
    field = policy.validate_pr_record(record)
    if field is not None:
        raise ResolveError("invalid PR record: %s" % (field,))
    return record


def _validated_open_main_prs(client):
    """The open-main PR list with every record validated. A malformed
    record cannot be scoped or matched, and skipping it could leave its
    head unmonitored, so it fails the whole resolve."""
    return [_require_pr_record(pr) for pr in client.list_open_main_prs()]


def _note_unmatched_summary(env, selector, numbers):
    """Record the unmatched workflow_run selector in the job summary,
    best effort: a summary-write failure must never change the exit code
    or stdout."""
    path = env.get("GITHUB_STEP_SUMMARY")
    if not path:
        return
    try:
        with open(path, "a", encoding="utf-8") as handle:
            handle.write("bits gate: workflow_run selectors matched no open-main PR; "
                         "scanning all open-main heads (numbers=%r)\n" % (numbers,))
    except OSError:
        # Best effort by the contract above: a failed summary write must
        # not change the exit code or stdout.
        pass


def resolve_shas(client, env):
    """The head SHAs to publish for this event, deduplicated and sorted.

    Every input arrives through ``env`` — the event name and its
    selectors; nothing is interpolated into a command or executed. Invalid
    input raises ResolveError and an API failure raises ApiError after
    the client's retries; more than MAX_RESOLVE_SHAS distinct SHAs raises
    ResolveError instead of truncating.
    """
    event = env.get("GITHUB_EVENT_NAME")
    if event == "pull_request_target":
        # A title/body edit cannot change any decision input (the policy
        # reads reviews, head SHA, membership/state), so it resolves to
        # nothing; the guard fails open — any base-change signal or other
        # action resolves normally.
        action = env.get("GITHUB_PR_ACTION", "")
        base_ref = env.get("GITHUB_CHANGES_BASE_REF", "")
        base_sha = env.get("GITHUB_CHANGES_BASE_SHA", "")
        if action == "edited" and not base_ref and not base_sha:
            return []
        number = _env_int(env, "GITHUB_PR_NUMBER")
        pr = client.get_pr(number)
        _require_pr_record(pr)
        shas = {pr["head"]["sha"]}
    elif event == "workflow_run":
        head_sha = _env_sha(env, "GITHUB_HEAD_SHA")
        selector = (_env_str(env, "GITHUB_HEAD_REPOSITORY"),
                    _env_str(env, "GITHUB_HEAD_BRANCH"))
        numbers = _env_pr_numbers(env, "GITHUB_PULL_REQUEST_NUMBERS")
        open_prs = _validated_open_main_prs(client)
        matched = [pr for pr in open_prs
                    if pr["number"] in numbers or _pr_selector(pr) == selector]
        if matched:
            selected = matched
        else:
            # Nothing matched — fork runs and stale number lists alike —
            # so the full open-main fallback keeps every head monitored.
            if numbers:
                _note_unmatched_summary(env, selector, numbers)
            selected = open_prs
        shas = {head_sha} | {pr["head"]["sha"] for pr in selected}
    elif event in ("schedule", "workflow_dispatch"):
        shas = {pr["head"]["sha"] for pr in _validated_open_main_prs(client)}
    else:
        raise ResolveError("unknown event name: %r" % (event,))
    if len(shas) > MAX_RESOLVE_SHAS:
        raise ResolveError("%d SHAs exceed the cap of %d" % (len(shas), MAX_RESOLVE_SHAS))
    return sorted(shas)


def _write_resolved_shas(env, shas):
    """The resolved SHAs as the ``shas`` step output through
    GITHUB_OUTPUT, or on stdout when unset, for local runs. An I/O
    failure surfaces as OSError to the caller, which exits 1."""
    payload = json.dumps(shas)
    output = env.get("GITHUB_OUTPUT")
    if output:
        with open(output, "a", encoding="utf-8") as handle:
            handle.write("shas=%s\n" % (payload,))
    else:
        print(payload)


def _build_arg_parser():
    parser = argparse.ArgumentParser(prog="bits_review_gate.py",
                                     description="Bits review merge gate")
    commands = parser.add_subparsers(dest="command", required=True)
    commands.add_parser("resolve", help="resolve the head SHAs to publish")
    publish = commands.add_parser(
        "publish", help="publish the validated decision for one head")
    publish.add_argument("--sha", required=True,
                         help="the 40-character head SHA to publish for")
    return parser


def main(argv=None, env=None, transport=None):
    """Run one CLI command and return the process exit code.

    Inputs reach Python only through ``env``. ``resolve`` exits 1 on
    invalid input, on an API failure after the client's retries, when
    more than MAX_RESOLVE_SHAS distinct SHAs would be emitted, or when
    the resolved SHA list cannot be written; it exits 0 only after
    writing the resolved SHA list. ``publish --sha H`` validates H (40
    lowercase hex characters) and exits 0 on a suppressed or published
    non-error decision and on an empty P(H); every other path — an
    invalid SHA, an error decision or a failed write — exits 1.
    """
    env = os.environ if env is None else env
    args = _build_arg_parser().parse_args(argv)
    repo = env.get("GITHUB_REPOSITORY") or ""
    owner, sep, name = repo.partition("/")
    if not (owner and sep and name):
        return 1
    client = GitHubClient(repo, transport=transport, env=env)
    if args.command == "publish":
        if _SHA_RE.fullmatch(args.sha) is None:
            return 1
        return _publish_status(args.sha, client, env.get("STATUS_TOKEN"))
    try:
        shas = resolve_shas(client, env)
    except (ResolveError, ApiError):
        return 1
    try:
        _write_resolved_shas(env, shas)
    except OSError:
        # The shas output is load-bearing for the publish job: a write
        # failure fails the run like a resolve failure, without a
        # traceback.
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
