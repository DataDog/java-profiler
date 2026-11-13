# Copyright 2026, Datadog, Inc.
"""Shared hermetic scaffold for the Bits review gate test families.

Stdlib-only infrastructure: fixture loaders, record, PR-record and
GraphQL-node builders, the REST-fixture to GraphQL-node data mapping used
to build test inputs, and a minimal injectable fake-transport base. No gate
behavior lives here. The REST to GraphQL mapping is a local data conversion for test inputs;
it claims no equivalence between the two remote APIs.
"""

import json
import os

FIXTURES_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), "fixtures", "bits_review_gate")
FIXTURE_FILES = {
    "pr985": "review-pr985-5872953227.json",
    "pr968": "review-pr968-5872101609.json",
}


def load_review_fixture(pr):
    """Return the parsed REST review record fixture for 'pr985' or 'pr968'."""
    with open(os.path.join(FIXTURES_DIR, FIXTURE_FILES[pr]), encoding="utf-8") as f:
        return json.load(f)


def load_review_fixtures():
    """Return both REST review record fixtures, keyed by PR."""
    return [load_review_fixture(pr) for pr in sorted(FIXTURE_FILES)]


def build_review_node(**overrides):
    """Return a GraphQL-shaped review node with exactly the node fields the
    adapter's query requests, plus per-case keyword overrides."""
    node = {
        "databaseId": 1,
        "state": "COMMENTED",
        "body": "review body",
        "submittedAt": "2026-11-12T09:30:55Z",
        "lastEditedAt": None,
        "commit": {"oid": "0" * 40},
        "author": {"__typename": "Bot", "login": "bot[bot]", "databaseId": 100},
    }
    node.update(overrides)
    return node


def build_review_record(**overrides):
    """Return a normalized policy record with exactly the record fields the
    adapter maps; last_edited_at carries the raw value, never a boolean."""
    record = {
        "id": 1,
        "author_typename": "Bot",
        "author_id": 100,
        "author_login": "bot[bot]",
        "state": "COMMENTED",
        "body": "review body",
        "commit_oid": "0" * 40,
        "submitted_at": "2026-11-12T09:30:55Z",
        "last_edited_at": None,
    }
    record.update(overrides)
    return record


def rest_review_to_node(rest):
    """Map a REST review fixture to a GraphQL node: body stays body,
    commit_id becomes commit.oid, user.id becomes author.databaseId,
    user.type becomes __typename, submitted_at becomes submittedAt, and
    lastEditedAt is null — the REST payload carries no edit timestamp."""
    user = rest["user"]
    return {
        "databaseId": rest["id"],
        "state": rest["state"],
        "body": rest["body"],
        "submittedAt": rest["submitted_at"],
        "lastEditedAt": None,
        "commit": {"oid": rest["commit_id"]},
        "author": {"__typename": user["type"], "login": user["login"], "databaseId": user["id"]},
    }


def build_pr_record(number=985, sha=None, base_ref="main", state="open", **overrides):
    """Return a pulls-list PR record carrying the fields the gate reads
    (number, head.sha, base.ref, state); keyword overrides merge on top."""
    record = {
        "number": number,
        "state": state,
        "head": {"sha": "1" * 40 if sha is None else sha},
        "base": {"ref": base_ref},
    }
    record.update(overrides)
    return record


def fixture_node(pr, **overrides):
    """A GraphQL review node derived from one supplied REST fixture through
    the single REST-to-GraphQL mapping; keyword overrides merge on top."""
    node = rest_review_to_node(load_review_fixture(pr))
    node.update(overrides)
    return node


class FakeTransport:
    """Minimal injectable transport base for the API and publish families.

    Serves queued responses in order, records every call for interleaving
    assertions, and raises queued exceptions. Families extend this base only
    for the cases they actually need, never by adding a second base.
    """

    def __init__(self, responses=()):
        self._responses = list(responses)
        self.calls = []

    def __call__(self, request):
        self.calls.append(request)
        if not self._responses:
            raise AssertionError("unexpected transport call: %r" % (request,))
        result = self._responses.pop(0)
        if isinstance(result, Exception):
            raise result
        return result
