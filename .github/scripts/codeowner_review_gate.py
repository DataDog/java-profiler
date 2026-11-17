# Copyright 2026, Datadog, Inc.
"""Sensitive-path code-owner review gate.

Companion of ``bits_review_gate.py``: publishes the ``codeowner-review/head``
commit status for the same resolved head SHAs, in the same trusted publish
job and with the same status token. A head that changes any path with a
CODEOWNERS entry beyond the repository-wide default rule requires an
approving review from a member of the owning team, by someone other than
the PR author. A head with no sensitive change passes without a review.
The decision is fail-closed: any API error or malformed input publishes
``failure``, never a pass.

CODEOWNERS is the single source of the sensitive-path list: the file keeps
the repository-wide default rule for change attribution, and every more
specific entry marks a sensitive path. Reviewer routing and this check
therefore cannot drift apart.
"""

import argparse
import fnmatch
import json
import os
import sys
import urllib.parse

import bits_review_gate as gate

STATUS_CONTEXT = "codeowner-review/head"
# Anchored to this file, not the process cwd: the workflow runs from the
# repository root, but a different cwd must not change the sensitive list.
CODEOWNERS_PATH = os.path.join(
    os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
    ".github", "CODEOWNERS")
#: The repository-wide default rule: it covers every path for change
#: attribution and never marks a path sensitive.
DEFAULT_RULE_PATTERN = "*"
#: The one team whose approval this gate accepts; every sensitive-path
#: entry in CODEOWNERS must name exactly this team (checked at load time).
OWNER_ORG = "DataDog"
OWNER_TEAM_SLUG = "profiling-java"
OWNER_TEAM = "@%s/%s" % (OWNER_ORG, OWNER_TEAM_SLUG)
CODEOWNERS_MAX_ENTRIES = 1024
#: The compare endpoint caps its file list and offers no pagination; a full
#: list is indistinguishable from a truncation and fails closed.
_COMPARE_FILE_CAP = 300


class CodeownerClient(gate.GitHubClient):
    """GitHubClient plus the two reads this gate adds: changed files and
    team membership. Pagination reuses the base client's helpers."""

    def team_logins(self, org, team_slug):
        """The login of every member of ``org``'s ``team_slug`` team, all
        pages, cached for the process lifetime. The read goes out with the
        membership token — the repository-scoped read token cannot
        authorize organization-team lookups — paginated with the same
        page-following rules as the base client's list reads."""
        cached = getattr(self, "_team_logins", None)
        if cached is None:
            url = "%s/orgs/%s/teams/%s/members?per_page=%d" % (
                self._api_url, org, team_slug, gate.REST_PER_PAGE)
            token = getattr(self, "_membership_token", None)
            pages = 0
            members = []
            while url is not None:
                body, link = self._fetch(url, token=token)
                try:
                    page = json.loads(body)
                except ValueError as error:
                    raise gate.ApiError("malformed JSON from %s" % (url,)) from error
                if not isinstance(page, list):
                    raise gate.ApiError("expected a JSON array from %s" % (url,))
                members.extend(page)
                pages += 1
                if pages >= gate.MAX_FETCH_PAGES:
                    raise gate.ApiError(
                        "team membership for %s exceeds %d pages"
                        % (team_slug, gate.MAX_FETCH_PAGES))
                url = gate._next_link(link, self._api_url)
            cached = frozenset(
                member.get("login") for member in members
                if isinstance(member, dict))
            self._team_logins = cached
        return cached

    def compare_files(self, base_ref, head_sha):
        """The changed files between ``base_ref`` and the immutable head
        SHA ``head_sha`` (three-dot compare, so the base side is the merge
        base): name plus status; renames carry both names.

        The compare response caps the file list at 300 entries and offers
        no pagination, so a full page is indistinguishable from a
        truncation and fails closed.
        """
        base = urllib.parse.quote(base_ref, safe="")
        url = "%s/repos/%s/compare/%s...%s" % (
            self._api_url, self._repo, base, head_sha)
        body, _ = self._fetch(url)
        try:
            document = json.loads(body)
        except ValueError as error:
            raise gate.ApiError("malformed JSON from %s" % (url,)) from error
        if not isinstance(document, dict) or not isinstance(document.get("files"), list):
            raise gate.ApiError("compare response for %s misses files" % (head_sha,))
        files = document["files"]
        if len(files) >= _COMPARE_FILE_CAP:
            raise gate.ApiError(
                "compare for %s reports %d files, at or above the %d cap"
                % (head_sha, len(files), _COMPARE_FILE_CAP))
        return files


def load_sensitive_patterns(path):
    """The sensitive-path patterns of a CODEOWNERS file: the pattern of
    every entry except the repository-wide default rule.

    One failure mode exists — an unreadable or oversized file — and it is
    fatal: without the list the check cannot distinguish sensitive paths,
    so the caller must publish failure rather than guess.
    """
    try:
        with open(path, encoding="utf-8") as handle:
            lines = handle.readlines()
    except OSError as error:
        raise gate.ApiError("unreadable %s: %s" % (path, error)) from error
    if len(lines) > CODEOWNERS_MAX_ENTRIES:
        raise gate.ApiError("%s exceeds %d entries" % (path, CODEOWNERS_MAX_ENTRIES))
    patterns = []
    for line in lines:
        entry = line.split("#", 1)[0].strip()
        if not entry:
            continue
        tokens = entry.split()
        pattern = tokens[0]
        if pattern == DEFAULT_RULE_PATTERN:
            continue
        # The gate approves by one fixed team; an entry naming any other
        # team would route reviewers there while this gate keeps demanding
        # this team's approval — reject instead of letting the two drift.
        owners = set(tokens[1:])
        if owners != {OWNER_TEAM}:
            raise gate.ApiError(
                "%s entry %r names owners %s; this gate only supports %s"
                % (path, pattern, sorted(owners), OWNER_TEAM))
        if not pattern.startswith("/"):
            # GitHub would match an unanchored pattern in any directory;
            # a whole-path fnmatch would let those paths escape the check,
            # so an unanchored entry is rejected instead of mis-evaluated.
            raise gate.ApiError(
                "%s entry %r is not root-anchored; prefix it with /"
                % (path, pattern))
        if pattern.endswith("/") and ("*" in pattern or "?" in pattern):
            # A wildcard directory pattern matches only under the loader's
            # literal-prefix rule, which under-blocks; reject the form.
            raise gate.ApiError(
                "%s entry %r combines a wildcard with a trailing slash; "
                "list the directory or files it covers"
                % (path, pattern))
        patterns.append(pattern)
    return patterns


def is_sensitive(path, patterns):
    """True when ``path`` matches one sensitive pattern.

    Supported grammar: root-anchored entries only (leading ``/``, dropped
    before matching, because the changed-file API reports paths without
    it) — exact paths, ``*``/``?`` wildcards and directory patterns with a
    trailing slash, which match every path inside the directory. An
    unanchored pattern is rejected by ``load_sensitive_patterns`` instead
    of being mis-evaluated: GitHub would match it in any directory while
    a whole-path fnmatch would let those paths escape the check.
    ``fnmatch`` lets ``*`` cross ``/``, which can only over-block a path
    GitHub attributes more narrowly — the fail-safe direction.
    """
    for pattern in patterns:
        if pattern.startswith("/"):
            pattern = pattern[1:]
        if pattern.endswith("/"):
            if path.startswith(pattern) or path.startswith(pattern[:-1] + "/"):
                return True
        elif "*" in pattern or "?" in pattern:
            if fnmatch.fnmatchcase(path, pattern):
                return True
        elif path == pattern or path.startswith(pattern + "/"):
            # GitHub treats a ``/dir`` entry as covering the directory's
            # contents too; the prefix match mirrors that without a
            # trailing slash.
            return True
    return False


def latest_review_by_login(records):
    """One record per author login: the latest by submission time, with
    the review id as tie-breaker — the same ordering rule the bits gate
    uses for its candidates."""
    latest = {}
    for record in records:
        login = record.get("author_login")
        if not isinstance(login, str) or not login:
            continue
        current = latest.get(login)
        if (current is None
                or (record.get("submitted_at") or "") > (current.get("submitted_at") or "")
                or (record.get("submitted_at") == current.get("submitted_at")
                    and (record.get("id") or 0) > (current.get("id") or 0))):
            latest[login] = record
    return latest


def owner_approval(records, author_login, team_logins, head):
    """True when some team member other than the PR author's latest
    review approves the evaluated head. Self-approval never counts: the
    author could otherwise satisfy the check alone. The approval must be
    bound to the head commit — without ``dismiss stale reviews``, an
    approval left on an earlier commit would otherwise survive a push
    that changes sensitive code."""
    for login, record in latest_review_by_login(records).items():
        if login == author_login:
            continue
        if (login in team_logins and record.get("state") == "APPROVED"
                and record.get("commit_oid") == head):
            return True
    return False


def _repo_url():
    repo = os.environ.get("GITHUB_REPOSITORY", "DataDog/java-profiler")
    return "https://github.com/" + repo


def evaluate_sha(sha, client, patterns):
    """The decision for one head SHA: ``(kind, state, description,
    target_url)``.

    Every open ``main`` PR whose head is ``sha`` must pass. The decision
    is fail-closed: an unreadable CODEOWNERS, a failed read or a
    malformed record publishes ``failure`` — a transient API outage must
    never yield a pass. ``kind`` is ``"empty"`` when no open PR sits at
    ``sha`` (or one moved away mid-read): the caller writes nothing, so a
    closed or advanced head cannot inherit a stale success.
    """
    try:
        open_prs = client.list_open_main_prs()
    except (gate.ApiError, gate.RateLimitError):
        return ("failure", "failure", "cannot evaluate: pulls read failed", None)
    members = []
    for pr in open_prs:
        if not isinstance(pr, dict):
            return ("failure", "failure", "cannot evaluate: malformed PR record", None)
        head = pr.get("head")
        # A record with a missing or malformed head SHA cannot be scoped to
        # this SHA: skipping it would leave its sensitive change unchecked,
        # so it fails the whole snapshot.
        if not isinstance(head, dict) or not isinstance(head.get("sha"), str):
            return ("failure", "failure", "cannot evaluate: malformed PR record", None)
        if head.get("sha") != sha:
            continue
        members.append(pr)
    decisions = []
    for pr in members:
        number = pr.get("number")
        user = pr.get("user")
        if not isinstance(number, int) or not isinstance(user, dict) \
                or not isinstance(user.get("login"), str):
            # Without a usable author identity the self-approval exclusion
            # cannot hold, so the record is malformed, not merely odd.
            return ("failure", "failure", "cannot evaluate: malformed PR record", None)
        author_login = user.get("login")
        base = pr.get("base")
        base_ref = base.get("ref") if isinstance(base, dict) else None
        if not isinstance(base_ref, str):
            return ("failure", "failure",
                    "cannot evaluate: malformed PR record", None)
        head_repo = (pr.get("head") or {}).get("repo")
        same_repo = (isinstance(head_repo, dict)
                     and head_repo.get("full_name") == client.repo)
        if not same_repo:
            # A fork head cannot be compared on the base repository with a
            # pinned SHA, and the live files read is racy: the author can
            # swap a sensitive head for a benign one for the duration of the
            # read. Fail closed instead of trusting a racy file list.
            decisions.append((number, "failure",
                              "cannot evaluate: fork pull request"))
            continue
        # Same-repo heads are read through the three-dot compare with the
        # evaluated SHA as the immutable head side; the PR files endpoint
        # always returns the PR's current head, so a push between the open-PR
        # listing and the read could pass a head that was never checked.
        try:
            files = client.compare_files(base_ref, sha)
        except (gate.ApiError, gate.RateLimitError):
            decisions.append((number, "failure",
                              "cannot evaluate: PR %d files read failed" % (number,)))
            continue
        filenames = []
        malformed_files = False
        for entry in files:
            if not isinstance(entry, dict):
                malformed_files = True
                break
            filename = entry.get("filename")
            renamed = entry.get("previous_filename")
            if not isinstance(filename, str) or not (
                    renamed is None or isinstance(renamed, str)):
                malformed_files = True
                break
            filenames.append(filename)
            if renamed:
                filenames.append(renamed)
        if malformed_files:
            decisions.append((number, "failure",
                              "cannot evaluate: PR %d files read failed" % (number,)))
            continue
        sensitive = [name for name in filenames if is_sensitive(name, patterns)]
        if not sensitive:
            decisions.append((number, "pass", None))
            continue
        try:
            records = [gate.normalize_review(node)
                       for node in client.fetch_reviews(number)]
        except (gate.ApiError, gate.RateLimitError):
            decisions.append((number, "failure",
                              "cannot evaluate: PR %d reviews read failed" % (number,)))
            continue
        # The roster is fetched lazily and fail-closed like every other
        # read: only a head with a sensitive-path change and a review read
        # behind it needs it.
        try:
            team_logins = client.team_logins(OWNER_ORG, OWNER_TEAM_SLUG)
        except (gate.ApiError, gate.RateLimitError):
            decisions.append((number, "failure",
                              "cannot evaluate: team roster read failed"))
            continue
        if owner_approval(records, author_login, team_logins, sha):
            decisions.append((number, "pass", None))
        else:
            decisions.append((
                number, "failure",
                "sensitive paths changed: approval from @DataDog/"
                "profiling-java required",
            ))
    failures = [decision for decision in decisions if decision[1] != "pass"]
    if failures:
        number, _, description = failures[0]
        return ("failure", "failure", description,
                "%s/pull/%d" % (_repo_url(), number))
    # Revalidate every contributing PR after the reads: a head that moved on
    # or a PR that closed between the listing and here must not leave a
    # success attached to this SHA — the next evaluation of the new head
    # publishes its own status instead.
    if not members:
        return ("empty", None, None, None)
    for pr in members:
        try:
            fresh = client.get_pr(pr["number"])
        except (gate.ApiError, gate.RateLimitError):
            return ("failure", "failure",
                    "cannot evaluate: PR %d revalidation failed" % (pr["number"],),
                    "%s/pull/%d" % (_repo_url(), pr["number"]))
        fresh_head = fresh.get("head") if isinstance(fresh, dict) else None
        if (not isinstance(fresh, dict) or fresh.get("state") != "open"
                or not isinstance(fresh_head, dict)
                or fresh_head.get("sha") != sha):
            return ("empty", None, None, None)
    return ("success", "success", "sensitive-path owner review satisfied", None)


def _selected_status(statuses):
    """The newest recorded status of this gate's context from its own
    creator, or None — other actors' statuses are never candidates for
    suppression."""
    latest = None
    for status in statuses:
        if not isinstance(status, dict):
            continue
        if (status.get("context") != STATUS_CONTEXT
                or (status.get("creator") or {}).get("login") != gate.STATUS_CREATOR):
            continue
        if latest is None or status.get("id", 0) > latest.get("id", 0):
            latest = status
    return latest


def _matches_status(status, payload):
    """True when the recorded status equals the payload in every field the
    write would carry."""
    return (status.get("state") == payload["state"]
            and status.get("description") == payload["description"]
            and status.get("target_url") == payload.get("target_url")
            and status.get("context") == payload["context"])


def publish(sha, client, status_token):
    """Evaluate one head SHA and publish its status. Returns the process
    exit code: 0 for success, 1 for failure or a failed write. The team
    roster is fetched only after evaluation asks for it: a head with no
    open PR spends one read, not two."""
    client._membership_token = status_token
    try:
        patterns = load_sensitive_patterns(CODEOWNERS_PATH)
    except gate.ApiError as error:
        kind, state, description, target_url = (
            "decision", "failure", "cannot evaluate: %s" % (error,), None)
    else:
        kind, state, description, target_url = evaluate_sha(sha, client, patterns)
    if kind == "empty":
        return 0
    # GitHub caps status descriptions at 140 characters; an oversized one is
    # rejected with 422 and would leave a stale status in place.
    description = description[:140]
    payload = {"state": state, "context": STATUS_CONTEXT, "description": description}
    if target_url:
        payload["target_url"] = target_url
    try:
        recorded = client.read_statuses(sha)
    except (gate.ApiError, gate.RateLimitError):
        recorded = None  # a failed read never suppresses a safety update
    if recorded is not None:
        current = _selected_status(recorded)
        if current is not None and _matches_status(current, payload):
            return 0 if state == "success" else 1
    try:
        client.create_status(sha, payload, status_token)
    except (gate.ApiError, gate.RateLimitError):
        return 1
    return 0 if state == "success" else 1


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = parser.add_subparsers(dest="command", required=True)
    publish_parser = sub.add_parser("publish")
    publish_parser.add_argument("--sha", required=True)
    args = parser.parse_args(argv)
    if not gate._SHA_RE.fullmatch(args.sha):
        parser.error("--sha must be a 40-hex commit SHA")
    repo = os.environ.get("GITHUB_REPOSITORY", "DataDog/java-profiler")
    client = CodeownerClient(repo)
    return publish(args.sha, client, os.environ.get("STATUS_TOKEN"))


if __name__ == "__main__":
    sys.exit(main())
