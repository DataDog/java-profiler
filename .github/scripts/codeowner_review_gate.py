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
import re
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
CODEOWNERS_MAX_LINES = 1024
#: The compare endpoint caps its file list and offers no pagination; a full
#: list is indistinguishable from a truncation and fails closed.
_COMPARE_FILE_CAP = 300


class FileCapExceeded(gate.ApiError):
    """The compare endpoint returned a full page: the head changed more
    files than the cap, and a truncated list cannot be told apart from a
    complete one. Distinct from a failed read so the published status can
    tell the author what to do about it."""


class CodeownerClient(gate.GitHubClient):
    """GitHubClient plus the two reads this gate adds: changed files and
    team membership. Pagination reuses the base client's helpers."""

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._membership_token = None
        self._team_logins = None

    def set_membership_token(self, token):
        """Arm the org-team reads with the status token: the repository-
        scoped read token cannot authorize organization-team lookups."""
        self._membership_token = token

    def _collect_member_login(self, entry, url):
        """The login of one member record, fail-closed: a malformed record
        shrinks the roster, and a shrunk roster could accept an approval
        from a non-member, so it is an error, not a skip."""
        if not isinstance(entry, dict) or not isinstance(entry.get("login"), str) \
                or not entry.get("login"):
            raise gate.ApiError("malformed member record from %s" % (url,))
        return entry["login"]

    def team_logins(self, org, team_slug):
        """The login of every member of ``org``'s ``team_slug`` team, all
        pages, cached for the process lifetime. The read goes out with the
        membership token — the repository-scoped read token cannot
        authorize organization-team lookups — paginated with the same
        page-following rules as the base client's list reads."""
        cached = self._team_logins
        if cached is None:
            url = "%s/orgs/%s/teams/%s/members?per_page=%d" % (
                self._api_url, org, team_slug, gate.REST_PER_PAGE)
            token = self._membership_token
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
                members.extend(
                    self._collect_member_login(entry, url) for entry in page)
                url = gate._next_link(link, self._api_url)
                if url is None:
                    # The last page is in hand; the cap only bounds a read
                    # that would continue, like the base client's pages.
                    break
                pages += 1
                if pages >= gate.MAX_FETCH_PAGES:
                    raise gate.ApiError(
                        "team membership for %s exceeds %d pages"
                        % (team_slug, gate.MAX_FETCH_PAGES))
            cached = frozenset(members)
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
        # The base is qualified as a branch: GitHub resolves an ambiguous
        # comparison base to a tag first, so a tag named like the branch
        # would shadow the merge base and blank the file list.
        base = urllib.parse.quote("refs/heads/" + base_ref, safe="")
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
            raise FileCapExceeded(
                "compare for %s reports %d files, at or above the %d cap; "
                "split the pull request"
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
    if len(lines) > CODEOWNERS_MAX_LINES:
        raise gate.ApiError(
            "%s exceeds %d lines" % (path, CODEOWNERS_MAX_LINES))
    patterns = []
    for line in lines:
        entry = line.split("#", 1)[0].strip()
        if not entry:
            continue
        tokens = entry.split()
        pattern = tokens[0]
        # The default rule gets the same owner check as every other entry:
        # a repo-wide rule naming another team would reroute attribution
        # while this gate keeps demanding this team's approval.
        owners = set(tokens[1:])
        if owners != {OWNER_TEAM}:
            raise gate.ApiError(
                "%s entry %r names owners %s; this gate only supports %s"
                % (path, pattern, sorted(owners), OWNER_TEAM))
        if pattern == DEFAULT_RULE_PATTERN:
            continue
        # The gate approves by one fixed team; an entry naming any other
        # team would route reviewers there while this gate keeps demanding
        # this team's approval — reject instead of letting the two drift.
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
    it) — exact paths, ``*``/``?`` wildcards and directory patterns with
    or without a trailing slash. An unanchored pattern is rejected by
    ``load_sensitive_patterns`` instead of being mis-evaluated: GitHub
    would match it in any directory while a whole-path fnmatch would let
    those paths escape the check.

    A wildcard entry matches the file itself and every ancestor directory
    of it: GitHub applies ``/src/*/secure`` to ``src/m/secure/a.py``, and
    matching only the complete filename would let that file pass
    unchecked. Every prefix runs through ``fnmatch``, so a trailing slash
    on a wildcard entry is harmless: it names the directory, which the
    ancestor prefixes already reach. A leading ``**/`` covers files at
    the repository root too — ``/**/*.kts`` also matches
    ``build.gradle.kts``, whose prefixes contain no ``/`` — so such a
    pattern is also matched without its ``**/`` prefix. ``fnmatch`` lets
    ``*`` cross ``/``, which can only over-block a path GitHub
    attributes more narrowly — the fail-safe direction.
    """
    parts = path.split("/")
    prefixes = ["/".join(parts[:end]) for end in range(1, len(parts) + 1)]
    for pattern in patterns:
        if pattern.startswith("/"):
            pattern = pattern[1:]
        if pattern.endswith("/"):
            pattern = pattern[:-1]
        if "*" in pattern or "?" in pattern:
            variants = [pattern]
            if pattern.startswith("**/"):
                variants.append(pattern[3:])
            if "/**/" in pattern:
                # GitHub's ** matches zero directories anywhere: /a/**/b
                # also covers a/b, which plain fnmatch cannot reach.
                variants.append(pattern.replace("/**/", "/", 1))
            if any(fnmatch.fnmatchcase(prefix, variant)
                   for variant in variants for prefix in prefixes):
                return True
        elif path == pattern or path.startswith(pattern + "/"):
            # GitHub treats a ``/dir`` entry as covering the directory's
            # contents too; the prefix match mirrors that without a
            # trailing slash.
            return True
    return False


_SUBMITTED_AT_RE = re.compile(
    r"^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(\.\d+)?Z$")


def _submitted_at_key(record):
    """The ordering key of a review record's submission time. The strict
    grammar admits fractional and whole seconds; as plain strings ``.5Z``
    sorts before ``Z``, so the key is (whole-second body, fractional part)
    with the trailing ``Z`` stripped from the whole-second body and
    insignificant trailing zeros stripped from the fraction — timestamps
    denoting the same instant must compare equal, so the id tie-breaker
    can decide."""
    stamp = record.get("submitted_at") or ""
    whole, _, fraction = stamp.partition(".")
    if whole.endswith("Z"):
        whole = whole[:-1]
    return (whole, fraction[:-1].rstrip("0") if fraction else "")


def _validated_reviews(nodes, number):
    """The normalized review records of one PR, fail-closed: a record the
    approval decision cannot read — no id, a null author login, a missing
    or unparseable ``submitted_at`` — is malformed input, not a review to
    skip. A dropped record could hide the superseding CHANGES_REQUESTED
    of an owner approval, so the decision must not be made from it. A
    PENDING review states no decision and carries none of these fields
    reliably, so it is skipped outright."""
    records = [gate.normalize_review(node) for node in nodes]
    for record in records:
        if record.get("state") == "PENDING":
            continue
        if (not isinstance(record.get("id"), int)
                or not isinstance(record.get("author_login"), str)
                or not record.get("author_login")
                or not isinstance(record.get("submitted_at"), str)
                or not _SUBMITTED_AT_RE.fullmatch(record["submitted_at"])):
            raise gate.ApiError(
                "malformed review record on PR %d" % (number,))
    return records


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
                or _submitted_at_key(record) > _submitted_at_key(current)
                or (_submitted_at_key(record) == _submitted_at_key(current)
                    and (record.get("id") or 0) > (current.get("id") or 0))):
            latest[login] = record
    return latest


def _deciding_reviews(records):
    """The records that can carry a review decision, in submission order:
    COMMENTED and PENDING records state no decision, so they never
    supersede an approval — GitHub likewise keeps an approval when its
    author later comments."""
    return [record for record in records
            if record.get("state") not in ("COMMENTED", "PENDING")]


def owner_approval(records, author_login, team_logins, head):
    """True when some team member other than the PR author's latest
    review approves the evaluated head. Self-approval never counts: the
    author could otherwise satisfy the check alone. The approval must be
    bound to the head commit — without ``dismiss stale reviews``, an
    approval left on an earlier commit would otherwise survive a push
    that changes sensitive code."""
    for login, record in latest_review_by_login(
            _deciding_reviews(records)).items():
        if login == author_login:
            continue
        if (login in team_logins and record.get("state") == "APPROVED"
                and record.get("commit_oid") == head):
            return True
    return False


def _repo_url(client):
    return "https://github.com/" + client.repo


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
    approved_prs = []
    approved_author = {}
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
        except FileCapExceeded as error:
            decisions.append((number, "failure", "cannot evaluate: %s" % (error,)))
            continue
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
            if entry.get("status") == "renamed" and (
                    not isinstance(renamed, str) or not renamed):
                # Without the old name the rename-away from a sensitive
                # path would pass unchecked, so the entry is malformed.
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
            records = _validated_reviews(
                client.fetch_reviews(number), number)
        except gate.RateLimitError:
            decisions.append((number, "failure",
                              "cannot evaluate: PR %d reviews read failed" % (number,)))
            continue
        except gate.ApiError as error:
            decisions.append((number, "failure", "cannot evaluate: %s" % (error,)))
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
            approved_prs.append(number)
            approved_author[number] = author_login
        else:
            decisions.append((
                number, "failure",
                "sensitive paths changed: approval from %s required" % (OWNER_TEAM,),
            ))
    failures = [decision for decision in decisions if decision[1] != "pass"]
    if failures:
        number, _, description = failures[0]
        return ("failure", "failure", description,
                "%s/pull/%d" % (_repo_url(client), number))
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
                    "%s/pull/%d" % (_repo_url(client), pr["number"]))
        # A malformed record is a failed read, not a settled one: treating
        # it as "moved or closed" would skip the write and leave any
        # recorded success standing.
        fresh_head = fresh.get("head") if isinstance(fresh, dict) else None
        if (not isinstance(fresh, dict)
                or fresh.get("state") not in ("open", "closed")
                or not isinstance(fresh_head, dict)
                or not isinstance(fresh_head.get("sha"), str)
                or not gate._SHA_RE.fullmatch(fresh_head["sha"])):
            return ("failure", "failure",
                    "cannot evaluate: PR %d revalidation failed" % (pr["number"],),
                    "%s/pull/%d" % (_repo_url(client), pr["number"]))
        if fresh["state"] != "open" or fresh_head["sha"] != sha:
            return ("empty", None, None, None)
    # An approval read earlier can be dismissed before the status lands:
    # the revalidation window is exactly when the author or a maintainer
    # would withdraw it. Re-read the reviews of every PR that passed on an
    # approval and require the approval to still hold on the fresh read.
    for number in approved_prs:
        try:
            fresh_records = _validated_reviews(
                client.fetch_reviews(number), number)
            # The roster is process-cached by now, but the read must stay
            # guarded on its own terms: a cache-less future must fail the
            # publish, not crash it before any status is written.
            team_logins = client.team_logins(OWNER_ORG, OWNER_TEAM_SLUG)
        except gate.RateLimitError:
            return ("failure", "failure",
                    "cannot evaluate: PR %d revalidation failed" % (number,),
                    "%s/pull/%d" % (_repo_url(client), number))
        except gate.ApiError as error:
            return ("failure", "failure", "cannot evaluate: %s" % (error,),
                    "%s/pull/%d" % (_repo_url(client), number))
        if not owner_approval(fresh_records, approved_author[number],
                              team_logins, sha):
            return ("failure", "failure",
                    "sensitive paths changed: approval from %s required"
                    % (OWNER_TEAM,),
                    "%s/pull/%d" % (_repo_url(client), number))
    return ("success", "success", "sensitive-path owner review satisfied", None)


def _selected_status(statuses):
    """The newest recorded status of this gate's context from its own
    creator, or None — other actors' statuses are never candidates for
    suppression."""
    latest = None
    for status in statuses:
        if not isinstance(status, dict):
            continue
        status_id = status.get("id")
        if not isinstance(status_id, int):
            # A status whose id is not an integer cannot be ordered; treat
            # it as malformed input, never as a candidate.
            continue
        creator = status.get("creator")
        if (status.get("context") != STATUS_CONTEXT
                or not isinstance(creator, dict)
                or creator.get("login") != gate.STATUS_CREATOR):
            continue
        if latest is None or status_id > latest.get("id", 0):
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
    client.set_membership_token(status_token)
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
    if not os.environ.get("STATUS_TOKEN"):
        parser.error("STATUS_TOKEN is not set; the roster read and the status "
                     "write cannot be authorized")
    repo = os.environ.get("GITHUB_REPOSITORY", "DataDog/java-profiler")
    client = CodeownerClient(repo)
    return publish(args.sha, client, os.environ.get("STATUS_TOKEN"))


if __name__ == "__main__":
    sys.exit(main())
