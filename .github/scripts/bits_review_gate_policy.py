# Copyright 2026, Datadog, Inc.
"""Pure policy core for the Bits review merge gate.

Standard library only, no I/O: the trusted-Bot allowlist, review-record and
PR-record validation, scope and candidacy classification, latest-candidate
selection, marker validation and the per-PR outcome precedence, the per-SHA
conjunction with its status payload (state, description, target URL) and
the full decision-input fingerprint. Records keep ``last_edited_at`` as
the raw adapter value; edited state derives from it and never replaces
it. The adapter calls these functions; they never call back.
"""

import datetime
import hashlib
import json
import re

#: The eight allowlisted Bits Bot databaseIds (design "Trusted result
#: recognition"). PASS is possible only from these identities.
TRUSTED_BOT_IDS = frozenset(
    {214633350, 88084959, 261164178, 298424163, 266080212, 266080418, 266081015, 266788760}
)

#: Review states the GitHub API may report for a review node.
REVIEW_STATES = ("PENDING", "COMMENTED", "APPROVED", "CHANGES_REQUESTED", "DISMISSED")

_MARKERS = ("autotest-meta", "datadog-code-review", "datadog-autotest")
_HEX40 = re.compile(r"[0-9a-f]{40}")
_COMMENT_RE = re.compile(r"<!--(.*?)-->", re.DOTALL)
_VERDICT_RE = re.compile(r"\bverdict=(\S*)")
_ENV_MARKER_RE = re.compile(r"<!--\s*datadog-autotest:v1:([^>]*?)\s*-->")
_REVIEWER_ID_MARKER = "<!-- datadog-code-review reviewer-id=bad90057-5c12-4101-ad47-d91c9dff0f90 -->"
_UTC = datetime.timezone.utc
_INSTANT_FLOOR = datetime.datetime.min.replace(tzinfo=_UTC)

#: The dedicated commit-status context this gate publishes.
STATUS_CONTEXT = "bits-review/head"

#: The contract's outcome-to-state mapping, verbatim; ``malformed:<sub>``
#: outcomes map to failure through the prefix rule in ``outcome_state``.
OUTCOME_STATES = {
    "pass": "success",
    "fail": "failure",
    "dismissed": "failure",
    "untrusted-origin": "failure",
    "edited-summary": "failure",
    "missing": "pending",
    "api-error": "error",
    "invalid-input": "error",
}

#: Conjunction severity of each status state; the greater value governs.
_STATE_SEVERITY = {"success": 0, "pending": 1, "failure": 2, "error": 3}

#: The status description never exceeds this many characters.
DESCRIPTION_LIMIT = 140


def _parse_iso8601(value):
    """Return the parsed instant, or None when value is not a parseable
    ISO-8601 string; the API's trailing Z spelling is accepted."""
    if not isinstance(value, str):
        return None
    text = value[:-1] + "+00:00" if value.endswith("Z") else value
    try:
        return datetime.datetime.fromisoformat(text)
    except ValueError:
        return None


def _is_positive_int(value):
    """True for a genuine positive int; bool is an int subclass and excluded."""
    return isinstance(value, int) and not isinstance(value, bool) and value > 0


def is_marked(body):
    """True when the body contains any of the three Bits marker substrings.
    A non-string body has no determinable marker state and is not marked."""
    return isinstance(body, str) and any(marker in body for marker in _MARKERS)


def is_edited(record):
    """True when the raw last_edited_at value is non-null; the record keeps
    the raw value and this predicate never replaces it."""
    return record.get("last_edited_at") is not None


def is_candidate(record):
    """A candidate is a Bot-authored review that is marked or edited.
    Known-User reviews are ignored even with copied markers; unedited
    unmarked Bot reviews are ignored."""
    return record.get("author_typename") == "Bot" and (
        is_marked(record.get("body")) or is_edited(record)
    )


def is_in_scope(record, head):
    """True when the review binds to the exact head SHA: commit_oid equals
    head, state is not PENDING and submitted_at is non-null. A null commit
    is out of scope."""
    return (
        record.get("commit_oid") is not None
        and record.get("commit_oid") == head
        and record.get("state") != "PENDING"
        and record.get("submitted_at") is not None
    )


def validate_review_record(record):
    """Return None when the record passes the contract's field checks, else a
    token naming the first failed field. A User-authored record is accepted
    without further checks: the wiring ignores it rather than trusting it.
    A marked or edited record whose author type is neither Bot nor User
    cannot be classified and fails validation."""
    typename = record.get("author_typename")
    if typename == "User":
        return None
    if not isinstance(record.get("body"), str):
        return "body"
    edited_raw = record.get("last_edited_at")
    if edited_raw is not None and _parse_iso8601(edited_raw) is None:
        return "last_edited_at"
    if not _is_positive_int(record.get("id")):
        return "id"
    state = record.get("state")
    if state not in REVIEW_STATES:
        return "state"
    commit_oid = record.get("commit_oid")
    if commit_oid is not None and (
        not isinstance(commit_oid, str) or _HEX40.fullmatch(commit_oid) is None
    ):
        return "commit_oid"
    submitted_at = record.get("submitted_at")
    if submitted_at is None:
        if state != "PENDING":
            return "submitted_at"
    elif _parse_iso8601(submitted_at) is None:
        return "submitted_at"
    if typename == "Bot" and not _is_positive_int(record.get("author_id")):
        return "author_id"
    if typename not in ("Bot", "User") and (is_marked(record.get("body")) or edited_raw is not None):
        return "author_typename"
    return None


def validate_pr_record(pr):
    """Return None when the PR record carries the contract's required
    fields — positive-int number, 40-hex head.sha, str base.ref, str
    state — else a token naming the first failed field."""
    if not _is_positive_int(pr.get("number")):
        return "number"
    head = pr.get("head")
    sha = head.get("sha") if isinstance(head, dict) else None
    if not isinstance(sha, str) or _HEX40.fullmatch(sha) is None:
        return "head.sha"
    base = pr.get("base")
    base_ref = base.get("ref") if isinstance(base, dict) else None
    if not isinstance(base_ref, str):
        return "base.ref"
    if not isinstance(pr.get("state"), str):
        return "state"
    return None


def _utc_instant(value):
    """The parsed instant normalized to UTC, or None when unparseable; a
    naive spelling reads as UTC."""
    parsed = _parse_iso8601(value)
    if parsed is None:
        return None
    if parsed.tzinfo is None:
        return parsed.replace(tzinfo=_UTC)
    return parsed.astimezone(_UTC)


def _possible_candidate(record):
    """True when the record could be a candidate: it is marked or edited, or
    its marker or edit state cannot be determined (non-string body,
    unparseable edit value). Only such records can hide a governing review."""
    body = record.get("body")
    if not isinstance(body, str):
        return True
    edited_raw = record.get("last_edited_at")
    if edited_raw is not None and _parse_iso8601(edited_raw) is None:
        return True
    return is_marked(body) or edited_raw is not None


def outcome_state(outcome_token):
    """The commit-status state for one outcome token; every
    ``malformed:<sub>`` outcome is ``failure``. An unknown token is a
    caller bug and raises."""
    if outcome_token in OUTCOME_STATES:
        return OUTCOME_STATES[outcome_token]
    if isinstance(outcome_token, str) and outcome_token.startswith("malformed:"):
        return "failure"
    raise ValueError("unknown outcome token: %r" % (outcome_token,))


def decide(per_pr_outcomes):
    """Conjoin the independent per-PR outcomes for one head SHA.

    ``per_pr_outcomes`` maps PR number to outcome token; each PR is judged
    on its own reviews only. Severity error > failure > pending > success
    picks the governing outcome, and the lowest PR number governs equal
    severities. Returns ``{"state", "reason", "governing_pr"}``, or None
    when no PR shares the head — an empty P(H) publishes nothing and is
    never success. A non-positive-int PR number or an unknown outcome
    token is a caller bug and raises."""
    if not per_pr_outcomes:
        return None
    best = None
    best_key = None
    for number, token in per_pr_outcomes.items():
        if not _is_positive_int(number):
            raise ValueError("PR number must be a positive int: %r" % (number,))
        state = outcome_state(token)
        # -number: the lowest PR number wins an equal-severity tie
        key = (_STATE_SEVERITY[state], -number)
        if best_key is None or key > best_key:
            best, best_key = (state, number, token), key
    return {"state": best[0], "governing_pr": best[1], "reason": best[2]}


def describe(reason, pr_number, detail=None):
    """``Bits review <reason> on PR #<n>[: <detail>]``, capped at
    DESCRIPTION_LIMIT characters. Numbers come from the API; a non-string
    reason or detail, or a non-positive-int PR number, is a caller bug and
    raises."""
    if not isinstance(reason, str):
        raise ValueError("reason must be a string: %r" % (reason,))
    if detail is not None and not isinstance(detail, str):
        raise ValueError("detail must be a string or None: %r" % (detail,))
    if not _is_positive_int(pr_number):
        raise ValueError("PR number must be a positive int: %r" % (pr_number,))
    text = "Bits review %s on PR #%d" % (reason, pr_number)
    if detail:
        text += ": %s" % (detail,)
    return text[:DESCRIPTION_LIMIT]


def target_url(repo, pr_number, review_id=None):
    """The governing review's URL when ``review_id`` is given, else the PR
    URL; both are built from API numbers only, never from body links. A
    non-positive-int number or review id, or an invalid repository, is a
    caller bug and raises."""
    if not isinstance(repo, str) or not repo:
        raise ValueError("repository must be a non-empty string: %r" % (repo,))
    if not _is_positive_int(pr_number):
        raise ValueError("PR number must be a positive int: %r" % (pr_number,))
    url = "https://github.com/%s/pull/%d" % (repo, pr_number)
    if review_id is None:
        return url
    if not _is_positive_int(review_id):
        raise ValueError("review id must be a positive int: %r" % (review_id,))
    return url + "#pullrequestreview-%d" % (review_id,)


def _jsonable(value):
    """A deterministic JSON-serializable stand-in for any raw value.
    Adapter values are JSON already; non-JSON values reduce to their type
    name so they still change the fingerprint by type."""
    if value is None or isinstance(value, (bool, int, float, str)):
        return value
    if isinstance(value, (list, tuple)):
        return [_jsonable(item) for item in value]
    if isinstance(value, dict):
        return {repr(key): _jsonable(item)
                for key, item in sorted(value.items(), key=lambda pair: repr(pair[0]))}
    return {"$type": type(value).__name__}


def _body_digest(body):
    """sha256 of a string body; any other raw value keeps its own typed
    canonical form so distinct non-string bodies still differ."""
    if isinstance(body, str):
        return "sha256:" + hashlib.sha256(body.encode("utf-8")).hexdigest()
    return "non-str:" + json.dumps(_jsonable(body), sort_keys=True, separators=(",", ":"))


def _pr_member(pr):
    """The fingerprint tuple of one P(H) member: (number, head.sha,
    base.ref, state), every value raw after type coercion."""
    if not isinstance(pr, dict):
        pr = {}
    head = pr.get("head")
    base = pr.get("base")
    return [
        _jsonable(pr.get("number")),
        _jsonable(head.get("sha") if isinstance(head, dict) else None),
        _jsonable(base.get("ref") if isinstance(base, dict) else None),
        _jsonable(pr.get("state")),
    ]


def _pr_sort_key(pr):
    number = pr.get("number") if isinstance(pr, dict) else None
    # Bucket 1 canonically self-orders via repr so invalid entries never
    # fall back to input order (same idiom as _sorted_flags).
    return (0, number) if _is_positive_int(number) else (1, repr(number))


def _record_member(record):
    """The fingerprint form of one normalized review record: every raw
    field after type coercion, the body as a digest. The raw
    ``last_edited_at`` value is kept, never a boolean."""
    if not isinstance(record, dict):
        record = {}
    return {
        "id": _jsonable(record.get("id")),
        "author_typename": _jsonable(record.get("author_typename")),
        "author_id": _jsonable(record.get("author_id")),
        "author_login": _jsonable(record.get("author_login")),
        "state": _jsonable(record.get("state")),
        "body": _body_digest(record.get("body")),
        "commit_oid": _jsonable(record.get("commit_oid")),
        "submitted_at": _jsonable(record.get("submitted_at")),
        "last_edited_at": _jsonable(record.get("last_edited_at")),
    }


def _record_sort_key(record):
    record_id = record.get("id") if isinstance(record, dict) else None
    # Bucket 1 canonically self-orders via repr so invalid entries never
    # fall back to input order (same idiom as _sorted_flags).
    return (0, record_id) if _is_positive_int(record_id) else (1, repr(record_id))


def _sorted_flags(flags):
    """Canonical flag list: every location, deterministically ordered —
    flag order is fetch order, not a decision input."""
    values = [_jsonable(flag) for flag in (flags if isinstance(flags, list) else [])]
    values.sort(key=repr)
    return values


def _fingerprint_payload(snapshot):
    """The canonical fingerprint structure of one SHA snapshot: the sorted
    P(H) members, every member's records sorted by id, and the error flags
    with their locations. Nothing partial: non-list prs or reviews values
    are carried raw instead of being dropped. The head is bound by each
    member's head.sha; the snapshot's own sha key is not an independent
    input and never reaches the digest."""
    if not isinstance(snapshot, dict):
        snapshot = {}
    prs = snapshot.get("prs")
    members = [_pr_member(pr) for pr in sorted(prs, key=_pr_sort_key)] if isinstance(prs, list) else _jsonable(prs)
    reviews = snapshot.get("reviews")
    review_members = {}
    if isinstance(reviews, dict):
        for number, records in reviews.items():
            if isinstance(records, list):
                review_members[repr(number)] = [
                    _record_member(record) for record in sorted(records, key=_record_sort_key)]
            else:
                review_members[repr(number)] = _jsonable(records)
    return {
        "prs": members,
        "reviews": review_members,
        "api_error": _sorted_flags(snapshot.get("api_error")),
        "invalid_input": _sorted_flags(snapshot.get("invalid_input")),
    }


def fingerprint(snapshot):
    """sha256 over canonical JSON (sorted keys, no extra whitespace) of
    every decision input of one SHA snapshot: the sorted P(H) members as
    (number, head.sha, base.ref, state), each member's records sorted by
    id with all raw fields (the body as a sha256 digest), and every
    api-error/invalid-input flag with its location. Derived outcomes, the
    snapshot's own sha key and unrelated PR fields never reach the digest;
    a decision computed on a snapshot whose fingerprint differs from the
    next one's is never reused."""
    canonical = json.dumps(_fingerprint_payload(snapshot), sort_keys=True, separators=(",", ":"))
    return hashlib.sha256(canonical.encode("utf-8")).hexdigest()


def _validate_markers(body):
    """Marker validation in the contract's order. Returns (sub-reason,
    verdict): sub-reason is None only for valid markers, and then verdict is
    exactly PASS or FAIL. Delivery markers, badges and image text are never
    consulted."""
    meta = [c for c in _COMMENT_RE.findall(body) if "autotest-meta" in c]
    if len(meta) != 1:
        return "missing-meta", None
    verdicts = _VERDICT_RE.findall(meta[0])
    if len(verdicts) > 1:
        return "conflicting-verdict", None
    if len(verdicts) != 1 or verdicts[0] not in ("PASS", "FAIL"):
        return "unknown-verdict", None
    if body.count(_REVIEWER_ID_MARKER) != 1:
        return "reviewer-id", None
    if _ENV_MARKER_RE.findall(body) != ["prod"]:
        return "env-marker", None
    return None, verdicts[0]


def latest_candidate(records, head=None):
    """The in-scope candidate with the greatest (UTC submitted_at, id).
    Selection precedes any validity, dismissal, origin, edit or marker check:
    the returned record may be any of those. A None head scopes out every
    record, so outcome() maps to missing — un-set/pending, not fail-closed:
    an error state here would block every unrelated head in the run."""
    best = None
    best_key = None
    for record in records:
        if not (is_candidate(record) and is_in_scope(record, head)):
            continue
        # Unparseable or invalid ids rank lowest; rule 1 already reported
        # every possible candidate carrying them, so this never changes an
        # outcome. The canonical member repr breaks remaining ties so
        # selection never depends on list order.
        rid = record.get("id") if _is_positive_int(record.get("id")) else -1
        member = _record_member(record)
        canonical = json.dumps(member, sort_keys=True, separators=(",", ":"))
        key = (_utc_instant(record.get("submitted_at")) or _INSTANT_FLOOR, rid,
               canonical)
        if best_key is None or key > best_key:
            best, best_key = record, key
    return best


def outcome(records, validation=validate_review_record, head=None, api_error=False):
    """The per-PR outcome token, the contract's rules 1-7 in exact order.
    records holds every normalized review record of the PR; validation is a
    callable returning validate_review_record's result for one record; head
    is the PR's 40-hex head SHA and None scopes out every record; api_error
    marks a failed review fetch, so no partial data is ever trusted."""
    if api_error:
        return "api-error"
    for record in records:
        if _possible_candidate(record) and validation(record) is not None:
            return "invalid-input"
    latest = latest_candidate(records, head)
    if latest is None:
        return "missing"
    if latest.get("state") == "DISMISSED":
        return "dismissed"
    if latest.get("author_typename") != "Bot" or latest.get("author_id") not in TRUSTED_BOT_IDS:
        return "untrusted-origin"
    if latest.get("last_edited_at") is not None:
        return "edited-summary"
    sub_reason, verdict = _validate_markers(latest.get("body"))
    if sub_reason is not None:
        return "malformed:" + sub_reason
    return "fail" if verdict == "FAIL" else "pass"
