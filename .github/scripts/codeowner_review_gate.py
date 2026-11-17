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
import os
import sys

import bits_review_gate as gate

STATUS_CONTEXT = "codeowner-review/head"
CODEOWNERS_PATH = os.path.join(".github", "CODEOWNERS")
#: The repository-wide default rule: it covers every path for change
#: attribution and never marks a path sensitive.
DEFAULT_RULE_PATTERN = "*"
#: The one team whose approval this gate accepts; every sensitive-path
#: entry in CODEOWNERS must name exactly this team (checked at load time).
OWNER_ORG = "DataDog"
OWNER_TEAM_SLUG = "profiling-java"
OWNER_TEAM = "@%s/%s" % (OWNER_ORG, OWNER_TEAM_SLUG)
CODEOWNERS_MAX_ENTRIES = 1024


class CodeownerClient(gate.GitHubClient):
    """GitHubClient plus the two reads this gate adds: changed files and
    team membership. Pagination reuses the base client's helpers."""

    def list_pr_files(self, number):
        """Every changed file of PR ``number``, all pages: name plus
        status; renames carry both names, so matching uses both."""
        url = "%s/repos/%s/pulls/%d/files?per_page=%d" % (
            self._api_url, self._repo, number, gate.REST_PER_PAGE)
        return self._fetch_json_pages(url)

    def team_logins(self, org, team_slug):
        """The login of every member of ``org``'s ``team_slug`` team, all
        pages, cached for the process lifetime."""
        cached = getattr(self, "_team_logins", None)
        if cached is None:
            url = "%s/orgs/%s/teams/%s/members?per_page=%d" % (
                self._api_url, org, team_slug, gate.REST_PER_PAGE)
            pages = self._fetch_json_pages(url)
            cached = frozenset(
                member.get("login") for member in pages
                if isinstance(member, dict))
            self._team_logins = cached
        return cached


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
    """The decision for one head SHA: ``(state, description, target_url)``.

    Every open ``main`` PR whose head is ``sha`` must pass. The
    decision is fail-closed: an unreadable CODEOWNERS, a failed pulls
    read, a malformed PR record or a failed files/reviews read publishes
    ``failure`` — a transient API outage must never yield a pass.
    """
    try:
        open_prs = client.list_open_main_prs()
    except (gate.ApiError, gate.RateLimitError):
        return ("failure", "cannot evaluate: pulls read failed", None)
    members = []
    for pr in open_prs:
        if not isinstance(pr, dict):
            return ("failure", "cannot evaluate: malformed PR record", None)
        head = pr.get("head")
        # A record with a missing or malformed head SHA cannot be scoped to
        # this SHA: skipping it would leave its sensitive change unchecked,
        # so it fails the whole snapshot.
        if not isinstance(head, dict) or not isinstance(head.get("sha"), str):
            return ("failure", "cannot evaluate: malformed PR record", None)
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
            return ("failure", "cannot evaluate: malformed PR record", None)
        author_login = user.get("login")
        try:
            files = client.list_pr_files(number)
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
        return ("failure", description, "%s/pull/%d" % (_repo_url(), number))
    if not members:
        return ("success", "no open pull request at this head", None)
    return ("success", "sensitive-path owner review satisfied", None)


def publish(sha, client, status_token):
    """Evaluate one head SHA and publish its status. Returns the process
    exit code: 0 for success, 1 for failure or a failed write. The team
    roster is fetched only after evaluation asks for it: a head with no
    open PR spends one read, not two."""
    try:
        patterns = load_sensitive_patterns(CODEOWNERS_PATH)
    except gate.ApiError as error:
        state, description = "failure", "cannot evaluate: %s" % (error,)
        target_url = None
    else:
        state, description, target_url = evaluate_sha(sha, client, patterns)
    payload = {"state": state, "context": STATUS_CONTEXT, "description": description}
    if target_url:
        payload["target_url"] = target_url
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
