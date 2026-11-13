# Copyright 2026, Datadog, Inc.
"""Validated-decision seam and publish CLI tests for the Bits review gate.

``revalidated_decision`` runs the real snapshot read through the shared
fake transport: every case asserts the return value and the exact
read-call interleaving, and every case proves zero write attempts — no
call leaves the pulls/GraphQL read URLs and none carries STATUS_TOKEN.
The seam itself never reads or writes commit statuses.

The publish families below run the real CLI (``main``) over the same
transport: ``--sha`` validation, the seam's exit mapping, suppression
against the selected latest app status, the POST payload and its
STATUS_TOKEN-only authorization, and the exit code of every write
branch.
"""

import json
import os
import sys
import unittest

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import bits_review_gate as gate  # noqa: E402

import bits_review_gate_testlib as testlib  # noqa: E402

REPO = "DataDog/java-profiler"
API = "https://api.example.test"
GRAPHQL = "https://api.example.test/graphql"
GITHUB_TOKEN = "gh-read-token"
STATUS_TOKEN = "status-write-token"
#: The publisher app login whose statuses are the gate's own output.
STATUS_CREATOR = "dd-octo-sts[bot]"
OTHER_CREATOR = "somebody-else[bot]"
PASS_DESCRIPTION = "Bits review pass on PR #968"
INVALID_INPUT_DESCRIPTION = "Bits review invalid-input on PR #968: pr-968"
#: The head under test; the pr968 fixture PASS binds to exactly this SHA.
HEAD = "1115eb583f475b62544d634bb12bf750ae913e04"
OTHER_HEAD = "1dcc3fa57582f2b595403f2b6a54e4464f352223"
PULLS_URL = "%s/repos/%s/pulls?state=open&base=main&per_page=100" % (API, REPO)
PASS_REVIEW_ID = 5872101609
FAIL_REVIEW_ID = 5872953227
UNLISTED_BOT_ID = 123456
PR968_URL = "https://github.com/%s/pull/968" % (REPO,)
PR969_URL = "https://github.com/%s/pull/969" % (REPO,)
PR985_URL = "https://github.com/%s/pull/985" % (REPO,)
PASS_REVIEW_URL = PR968_URL + "#pullrequestreview-%d" % (PASS_REVIEW_ID,)
FAIL_REVIEW_URL = PR985_URL + "#pullrequestreview-%d" % (FAIL_REVIEW_ID,)


class FakeResponse:
    """A recorded HTTP response: status, bytes body, optional Link header."""

    def __init__(self, status, body=b"[]", link=None):
        self.status = status
        self._body = body if isinstance(body, bytes) else json.dumps(body).encode("utf-8")
        self.headers = {"Link": link} if link else {}

    def read(self):
        return self._body


def make_client(transport):
    return gate.GitHubClient(REPO, transport=transport, env={
        "GITHUB_API_URL": API, "GITHUB_GRAPHQL_URL": GRAPHQL,
        "GITHUB_TOKEN": GITHUB_TOKEN, "STATUS_TOKEN": STATUS_TOKEN})


def publish_env():
    """The publish CLI's environment: the repository, the read API
    endpoints, the read token and the status token."""
    return {"GITHUB_REPOSITORY": REPO, "GITHUB_API_URL": API,
            "GITHUB_GRAPHQL_URL": GRAPHQL, "GITHUB_TOKEN": GITHUB_TOKEN,
            "STATUS_TOKEN": STATUS_TOKEN}


def publish_env_without_status_token():
    """The publish environment with the status token removed: the write
    cannot authenticate and must fail closed."""
    env = publish_env()
    del env["STATUS_TOKEN"]
    return env


def reviews_page(nodes, has_next=False, cursor="cursor-1"):
    return {"data": {"repository": {"pullRequest": {"reviews": {
        "nodes": nodes,
        "pageInfo": {"hasNextPage": has_next, "endCursor": cursor}}}}}}


def failed_reviews_page():
    """A 200 GraphQL response carrying an errors member: fail-closed."""
    page = reviews_page([])
    page["errors"] = [{"message": "Something went wrong"}]
    return FakeResponse(200, page)


def member(number=968, sha=HEAD, base_ref="main", state="open"):
    return testlib.build_pr_record(number=number, sha=sha, base_ref=base_ref, state=state)


def pass_node():
    """The pr968 fixture: an unedited allowlisted valid PASS at HEAD."""
    return testlib.fixture_node("pr968")


def fail_node():
    """The pr985 fixture FAIL, rebound to the head under test."""
    return testlib.fixture_node("pr985", commit={"oid": HEAD})


def snapshot_script(open_prs, reviews_by_number, head=HEAD):
    """(responses, expected read URLs) of one scripted snapshot: the pulls
    page, then one reviews page per member (head == the snapshot's head)
    in list order. A reviews value may be a prepared response, e.g. a
    failed page."""
    responses = [FakeResponse(200, open_prs)]
    urls = [PULLS_URL]
    for pr in open_prs:
        pr_head = pr.get("head") if isinstance(pr, dict) else None
        if isinstance(pr_head, dict) and pr_head.get("sha") == head:
            value = reviews_by_number[pr["number"]]
            responses.append(value if isinstance(value, FakeResponse)
                             else FakeResponse(200, reviews_page(value)))
            urls.append(GRAPHQL)
    return responses, urls


def failed_pulls_script():
    """(responses, expected read URLs) of one snapshot whose pulls read
    fails without a retry (a 4xx response)."""
    return [FakeResponse(404)], [PULLS_URL]


def status_post_url(sha):
    return "%s/repos/%s/statuses/%s" % (API, REPO, sha)


def status_record(state="success", description=PASS_DESCRIPTION,
                  target_url=PASS_REVIEW_URL, context="bits-review/head",
                  creator=STATUS_CREATOR, created_at="2026-11-12T12:00:00Z",
                  status_id=100):
    """One REST commit-status record, as the statuses endpoint returns
    them: the compared fields plus the creator and ordering inputs."""
    return {"state": state, "context": context, "description": description,
            "target_url": target_url, "creator": {"login": creator},
            "created_at": created_at, "id": status_id}


def pass_snapshot():
    """The stable all-pass snapshot whose decision publishes success."""
    return snapshot_script([member()], {968: [pass_node()]})


def invalid_input_snapshot():
    """The stable snapshot whose member decision is an invalid-input
    error."""
    broken = testlib.build_review_node(
        databaseId=5873000001, submittedAt="2026-11-12T12:00:00Z",
        commit={"oid": HEAD}, body=testlib.load_review_fixture("pr985")["body"],
        lastEditedAt="not-a-timestamp")
    return snapshot_script([member()], {968: [broken]})


def rate_limited_response(status=429, headers=None):
    """A rate-limited response whose honor window (Retry-After 600 s)
    exceeds the cap, so the read fails fast with RateLimitError."""
    response = FakeResponse(status, [])
    response.headers = {"Retry-After": "600"} if headers is None else headers
    return response


def statuses_read_url(sha=HEAD):
    return "%s/repos/%s/commits/%s/statuses?per_page=100" % (API, REPO, sha)


def publish_script(decision_snapshot, status_pages=(), post_response=None):
    """The transport queue of one full publish run: the decision's
    revalidated snapshot pair, then every status page, then the POST
    response when a write is expected."""
    responses = decision_snapshot[0] + decision_snapshot[0] + list(status_pages)
    if post_response is not None:
        responses.append(post_response)
    return responses


class SeamTestCase(unittest.TestCase):
    """Shared runner: the real seam, the exact interleaving assertion and
    the zero-write-attempt proof applied to every T7 case — no call leaves
    the read URLs (pulls, GraphQL reviews), none reads or writes statuses,
    and every call carries only GITHUB_TOKEN, never STATUS_TOKEN."""

    def run_seam(self, *scripts):
        responses, expected = [], []
        for responses_part, urls_part in scripts:
            responses.extend(responses_part)
            expected.extend(urls_part)
        transport = testlib.FakeTransport(responses)
        result = gate.revalidated_decision(HEAD, make_client(transport))
        self.assertEqual([call.full_url for call in transport.calls], expected)
        for call in transport.calls:
            self.assertIn(call.full_url, (PULLS_URL, GRAPHQL))
            self.assertEqual(call.headers.get("Authorization"), "Bearer " + GITHUB_TOKEN)
            for value in call.headers.values():
                self.assertNotIn(STATUS_TOKEN, value)
        return result, transport


class EmptySnapshotTest(SeamTestCase):
    """A successfully read empty P(H) returns ("empty", None) and reads
    nothing else."""

    def test_empty_p_h_returns_empty_from_one_snapshot_read(self):
        open_prs = [member(969, sha=OTHER_HEAD)]
        result, transport = self.run_seam(snapshot_script(open_prs, {}))
        self.assertEqual(result, ("empty", None))
        self.assertEqual(len(transport.calls), 1)


class StableDecisionTest(SeamTestCase):
    """A stable snapshot pair returns the exact decision payload of the
    revalidated read; D is asserted exactly and the two-snapshot read is
    pinned."""

    def test_stable_snapshot_returns_the_exact_success_payload(self):
        script = snapshot_script([member()], {968: [pass_node()]})
        result, _ = self.run_seam(script, script)
        self.assertEqual(result[0], "stable")
        self.assertEqual(result[1], {
            "state": "success",
            "reason": "pass",
            "governing_pr": 968,
            "description": "Bits review pass on PR #968",
            "target_url": PASS_REVIEW_URL,
            "context": "bits-review/head",
        })

    def test_non_decision_input_fields_do_not_change_the_decision(self):
        """PR fields outside the decision inputs (title, draft) change
        nothing the decision reads: the payload stays the success."""
        changed = member()
        changed["title"] = "renamed after the read"
        changed["draft"] = True
        result, transport = self.run_seam(snapshot_script([changed], {968: [pass_node()]}),
                                          snapshot_script([changed], {968: [pass_node()]}))
        self.assertEqual(result[0], "stable")
        self.assertEqual(result[1]["state"], "success")
        self.assertEqual(len(transport.calls), 4)

    def test_stable_fail_payload_names_the_governing_review(self):
        script = snapshot_script([member(985)], {985: [fail_node()]})
        result, _ = self.run_seam(script, script)
        self.assertEqual(result[0], "stable")
        self.assertEqual(result[1], {
            "state": "failure",
            "reason": "fail",
            "governing_pr": 985,
            "description": "Bits review fail on PR #985",
            "target_url": FAIL_REVIEW_URL,
            "context": "bits-review/head",
        })

    def test_shared_head_pair_with_one_pass_and_one_missing_is_pending(self):
        prs = [member(968), member(969)]
        reviews = {968: [pass_node()], 969: []}
        script = snapshot_script(prs, reviews)
        result, _ = self.run_seam(script, script)
        self.assertEqual(result[0], "stable")
        self.assertEqual(result[1], {
            "state": "pending",
            "reason": "missing",
            "governing_pr": 969,
            "description": "Bits review missing on PR #969",
            "target_url": PR969_URL,
            "context": "bits-review/head",
        })

    def test_success_requires_every_member_to_pass(self):
        both_pass = [member(968), member(969)]
        reviews = {968: [pass_node()],
                   969: [testlib.fixture_node("pr968", databaseId=PASS_REVIEW_ID + 1)]}
        script = snapshot_script(both_pass, reviews)
        result, _ = self.run_seam(script, script)
        self.assertEqual((result[0], result[1]["state"]), ("stable", "success"))
        self.assertEqual(result[1]["governing_pr"], 968)
        pass_and_fail = [member(968), member(985)]
        reviews = {968: [pass_node()], 985: [fail_node()]}
        script = snapshot_script(pass_and_fail, reviews)
        result, _ = self.run_seam(script, script)
        self.assertEqual(result[1]["state"], "failure")
        self.assertNotEqual(result[1]["reason"], "pass")


class ErrorDecisionTest(SeamTestCase):
    """api-error and invalid-input flags propagate into stable decisions
    as error decisions; the stale success is never returned."""

    def test_invalid_input_review_gives_a_stable_error_decision(self):
        marked_body = testlib.load_review_fixture("pr985")["body"]
        broken = testlib.build_review_node(
            databaseId=5873000001, submittedAt="2026-11-12T12:00:00Z",
            commit={"oid": HEAD}, body=marked_body, lastEditedAt="not-a-timestamp")
        reviews = {968: [pass_node(), broken]}
        script = snapshot_script([member()], reviews)
        result, _ = self.run_seam(script, script)
        self.assertEqual((result[0], result[1]["state"], result[1]["reason"]),
                         ("stable", "error", "invalid-input"))
        self.assertEqual(result[1]["description"],
                         "Bits review invalid-input on PR #968: pr-968")

    def test_malformed_pr_record_forces_error_over_clean_members(self):
        malformed = testlib.build_pr_record(number=7, sha="not-hex")
        prs = [member(), malformed]
        reviews = {968: [pass_node()]}
        script = snapshot_script(prs, reviews)
        result, transport = self.run_seam(script, script)
        self.assertEqual((result[0], result[1]["state"], result[1]["reason"]),
                         ("stable", "error", "invalid-input"))
        self.assertEqual(result[1]["governing_pr"], 968)
        self.assertEqual(result[1]["description"],
                         "Bits review invalid-input on PR #968: pr-record:head.sha")
        self.assertEqual(result[1]["target_url"], PR968_URL)
        self.assertEqual(len(transport.calls), 4)

    def test_failed_pulls_read_gives_a_stable_member_less_error_decision(self):
        """No PR could be scoped at all: the decision is still an error —
        never empty (the read did not succeed) — and, with no API PR
        number in the snapshot, description and target URL stay None."""
        result, transport = self.run_seam(failed_pulls_script(), failed_pulls_script())
        self.assertEqual(result[0], "stable")
        self.assertEqual(result[1], {
            "state": "error",
            "reason": "api-error",
            "governing_pr": None,
            "description": None,
            "target_url": None,
            "context": "bits-review/head",
        })
        self.assertEqual(len(transport.calls), 2)

    def test_pr_record_level_flag_outranks_a_member_api_error_in_reason_attribution(self):
        # The reason names the class of the flag that forced the level: a
        # malformed pr-record beats a member reviews read failure, and the
        # description renders the invalid-input flags, not the member's.
        malformed = testlib.build_pr_record(number=7, sha="not-hex")
        prs = [member(), malformed]
        script = snapshot_script(prs, {968: failed_reviews_page()})
        result, _ = self.run_seam(script, script)
        self.assertEqual((result[0], result[1]["state"], result[1]["reason"]),
                         ("stable", "error", "invalid-input"))
        self.assertEqual(result[1]["governing_pr"], 968)
        self.assertEqual(result[1]["description"],
                         "Bits review invalid-input on PR #968: pr-record:head.sha")


class FingerprintChangeLoopTest(SeamTestCase):
    """Every decision-input class changed between S(i) and S(i+1) forces a
    third snapshot read and never returns the stale D(i): the returned
    decision is recomputed from the changed snapshot."""

    def loop_result(self, first, changed):
        """S1, the changed S2 twice: three snapshots, six reads."""
        return self.run_seam(first, changed, changed)

    def loop_cases(self):
        """(name, S2 open_prs, S2 reviews, expected decision asserts):
        every fingerprint input class mutated away from the pass
        snapshot."""
        edited_pass = testlib.fixture_node("pr968",
                                           lastEditedAt="2026-11-12T13:00:00Z")
        dismissed_pass = testlib.fixture_node("pr968", state="DISMISSED")
        unlisted_author = testlib.fixture_node("pr968", author={
            "__typename": "Bot", "login": "other[bot]", "databaseId": 123456})
        user_author = testlib.fixture_node("pr968", author={
            "__typename": "User", "login": "human", "databaseId": 88084959})
        changed_login = testlib.fixture_node("pr968", author={
            "__typename": "Bot", "login": "renamed[bot]", "databaseId": 88084959})
        changed_commit = testlib.fixture_node("pr968", commit={"oid": "2" * 40})
        changed_submitted = testlib.fixture_node(
            "pr968", submittedAt="2026-11-12T10:31:55Z")
        new_review_id = testlib.fixture_node("pr968", databaseId=PASS_REVIEW_ID + 1)
        return [
            ("base-ref", [member(base_ref="develop")], {968: [pass_node()]},
             ("success", 968)),
            ("pr-state", [member(state="closed")], {968: [pass_node()]},
             ("success", 968)),
            ("new-fail-review", [member()], {968: [fail_node()]},
             ("failure", 968)),
            ("edited-pass", [member()], {968: [edited_pass]},
             ("failure", 968)),
            ("dismissed-pass", [member()], {968: [dismissed_pass]},
             ("failure", 968)),
            ("unlisted-author", [member()], {968: [unlisted_author]},
             ("failure", 968)),
            ("user-author", [member()], {968: [user_author]},
             ("pending", 968)),
            ("author-login", [member()], {968: [changed_login]},
             ("success", 968)),
            ("commit-oid", [member()], {968: [changed_commit]},
             ("pending", 968)),
            ("submitted-at", [member()], {968: [changed_submitted]},
             ("success", 968)),
            ("new-review-id", [member()], {968: [new_review_id]},
             ("success", 968)),
        ]

    def test_every_input_class_loops_and_never_returns_the_stale_decision(self):
        first = snapshot_script([member()], {968: [pass_node()]})
        for name, prs, reviews, (state, governing) in self.loop_cases():
            with self.subTest(case=name):
                changed = snapshot_script(prs, reviews)
                result, transport = self.loop_result(first, changed)
                self.assertEqual(result[0], "stable")
                self.assertEqual(result[1]["state"], state)
                if governing is not None:
                    self.assertEqual(result[1]["governing_pr"], governing)
                # Three snapshots: the stale S1 never survives as the
                # decision, and the loop revalidated S2 against S3.
                self.assertEqual(len(transport.calls), 6)

    def test_edited_pass_never_publishes_a_stale_success(self):
        """The gate's own threat: an edit landing between S1 and S2 turns
        the published decision into the edited-summary failure."""
        edited = testlib.fixture_node("pr968", lastEditedAt="2026-11-12T13:00:00Z")
        first = snapshot_script([member()], {968: [pass_node()]})
        changed = snapshot_script([member()], {968: [edited]})
        result, _ = self.loop_result(first, changed)
        self.assertEqual((result[0], result[1]["state"], result[1]["reason"]),
                         ("stable", "failure", "edited-summary"))

    def test_flickering_input_returns_the_last_revalidated_decision(self):
        """S1 pass, S2 edited, S3 and S4 pass again: every iteration
        recomputes — the returned success is the final matched pair's,
        never the intermediate edited failure nor a frozen earlier read."""
        edited = testlib.fixture_node("pr968", lastEditedAt="2026-11-12T13:00:00Z")
        pass_script = snapshot_script([member()], {968: [pass_node()]})
        edited_script = snapshot_script([member()], {968: [edited]})
        result, transport = self.run_seam(pass_script, edited_script,
                                          pass_script, pass_script)
        self.assertEqual((result[0], result[1]["state"], result[1]["reason"]),
                         ("stable", "success", "pass"))
        self.assertEqual(len(transport.calls), 8)

    def test_member_head_moving_away_empties_the_snapshot(self):
        """The member's head no longer matches the published SHA: the
        changed snapshot is an empty P(H), returned after two reads."""
        first = snapshot_script([member()], {968: [pass_node()]})
        moved = snapshot_script([member(sha=OTHER_HEAD)], {})
        result, transport = self.run_seam(first, moved)
        self.assertEqual(result, ("empty", None))
        self.assertEqual(len(transport.calls), 3)

    def test_membership_added_loops_and_conjoins_the_new_member(self):
        """A second PR sharing the head appears in S2: the decision is
        recomputed over both members, never the single-member stale D."""
        first = snapshot_script([member()], {968: [pass_node()]})
        both = [member(968), member(969)]
        changed = snapshot_script(both, {968: [pass_node()], 969: []})
        result, transport = self.loop_result(first, changed)
        self.assertEqual((result[0], result[1]["state"], result[1]["reason"]),
                         ("stable", "pending", "missing"))
        self.assertEqual(result[1]["governing_pr"], 969)
        # S1 reads one member (2 calls); S2 and S3 read two (3 calls each).
        self.assertEqual(len(transport.calls), 8)

    def test_api_error_appearing_in_s2_loops_to_the_error_decision(self):
        first = snapshot_script([member()], {968: [pass_node()]})
        changed = snapshot_script([member()], {968: failed_reviews_page()})
        result, _ = self.loop_result(first, changed)
        self.assertEqual((result[0], result[1]["state"]), ("stable", "error"))

    def test_invalid_input_appearing_in_s2_loops_to_the_error_decision(self):
        broken = testlib.build_review_node(
            databaseId=5873000001, submittedAt="2026-11-12T12:00:00Z",
            commit={"oid": HEAD}, body=testlib.load_review_fixture("pr985")["body"],
            lastEditedAt="not-a-timestamp")
        first = snapshot_script([member()], {968: [pass_node()]})
        changed = snapshot_script([member()], {968: [broken]})
        result, _ = self.loop_result(first, changed)
        self.assertEqual((result[0], result[1]["state"], result[1]["reason"]),
                         ("stable", "error", "invalid-input"))


class UnstableSnapshotTest(SeamTestCase):
    """Three consecutive fingerprint mismatches give up: (\"unstable\",
    None) after exactly four snapshot reads."""

    def test_three_mismatches_return_unstable_after_four_snapshots(self):
        edited = testlib.fixture_node("pr968", lastEditedAt="2026-11-12T13:00:00Z")
        dismissed = testlib.fixture_node("pr968", state="DISMISSED")
        unlisted = testlib.fixture_node("pr968", author={
            "__typename": "Bot", "login": "other[bot]", "databaseId": 123456})
        scripts = [snapshot_script([member()], {968: [pass_node()]}),
                   snapshot_script([member()], {968: [edited]}),
                   snapshot_script([member()], {968: [dismissed]}),
                   snapshot_script([member()], {968: [unlisted]})]
        result, transport = self.run_seam(*scripts)
        self.assertEqual(result, ("unstable", None))
        self.assertEqual(len(transport.calls), 8)
        for call in transport.calls:
            self.assertNotIn("/statuses", call.full_url)


class ZeroWriteAttemptTest(SeamTestCase):
    """The seam itself never reads or writes commit statuses: it returns
    values only, and every transport call stays on the two read URLs."""

    def test_no_case_ever_touches_the_statuses_endpoint(self):
        script = snapshot_script([member()], {968: [pass_node()]})
        _, transport = self.run_seam(script, script)
        self.assertTrue(transport.calls)
        for call in transport.calls:
            self.assertNotIn("/statuses", call.full_url)
            # Only the GraphQL reviews read may carry a body; a write is a
            # data-carrying call to any other URL.
            if call.data is not None:
                self.assertEqual(call.full_url, GRAPHQL)


class PublishTestCase(unittest.TestCase):
    """The real publish CLI (``main``) over the shared fake transport."""

    def run_publish(self, responses, sha=HEAD, env=None):
        transport = testlib.FakeTransport(responses)
        code = gate.main(["publish", "--sha", sha],
                         env=env if env is not None else publish_env(),
                         transport=transport)
        return code, transport

    def post_calls(self, transport, sha=HEAD):
        return [call for call in transport.calls
                if call.full_url == status_post_url(sha)]

    def assert_write_tokens(self, transport, sha=HEAD):
        """Every read carries GITHUB_TOKEN and never STATUS_TOKEN; the one
        POST carries STATUS_TOKEN."""
        self.assertTrue(transport.calls)
        for call in transport.calls:
            auth = call.headers.get("Authorization")
            if call.full_url == status_post_url(sha):
                self.assertEqual(auth, "Bearer " + STATUS_TOKEN)
            else:
                self.assertEqual(auth, "Bearer " + GITHUB_TOKEN)


class PublishShaValidationTest(PublishTestCase):
    """--sha is validated before anything is read: an invalid head never
    reaches the transport."""

    def test_invalid_sha_exits_1_without_any_transport_call(self):
        invalid = ("", "1" * 39, "1" * 41, "z" * 40, "1" * 39 + "A",
                   "Z" * 40, "1" * 20 + "g" * 20)
        for sha in invalid:
            code, transport = self.run_publish([], sha=sha)
            self.assertEqual(code, 1)
            self.assertEqual(transport.calls, [])


class RateLimitPublishTest(PublishTestCase):
    """Rate-limited reads failing past the honor cap publish diagnosable
    error decisions: the description names the rate-limit flag."""

    def test_null_graphql_root_publishes_the_blocking_error_status(self):
        # A JSON `null` root must fail closed through ApiError into an
        # error decision that is published — not crash the publisher with
        # AttributeError before the blocking status is written.
        null_root = FakeResponse(200, b"null")
        script = snapshot_script([member()], {968: null_root})
        code, transport = self.run_publish(publish_script(
            script, [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 1)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        payload = json.loads(posts[0].data)
        self.assertEqual(payload["state"], "error")
        self.assertEqual(payload["description"],
                         "Bits review api-error on PR #968: pr-968/reviews")
        self.assert_write_tokens(transport)

    def test_rate_limited_reviews_read_names_the_rate_limit_in_the_description(self):
        # A reviews read failing past the honor cap flags the member as
        # pr-<n>/reviews:rate-limit; the published description names it.
        script = snapshot_script([member()], {968: rate_limited_response()})
        code, transport = self.run_publish(publish_script(
            script, [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 1)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        payload = json.loads(posts[0].data)
        self.assertEqual(payload["state"], "error")
        self.assertEqual(payload["description"],
                         "Bits review api-error on PR #968: pr-968/reviews:rate-limit")
        self.assert_write_tokens(transport)

    def test_rate_limited_pulls_read_still_fails_closed_and_writes(self):
        # A pulls read failing past the honor cap must produce a
        # member-less error decision, not an empty one: the snapshot-level
        # filter matches pulls:rate-limit, so the write is attempted and
        # the run exits 1.
        script = ([rate_limited_response()], [PULLS_URL])
        code, transport = self.run_publish(publish_script(
            script, [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 1)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        self.assertEqual(json.loads(posts[0].data),
                         {"state": "error", "context": "bits-review/head"})
        self.assert_write_tokens(transport)

class SeamExitMappingTest(PublishTestCase):
    """The seam's empty return maps to exit 0 and its unstable return to
    exit 1, both with zero write calls — and no status read at all."""

    def test_empty_p_h_exits_0_with_no_status_read_or_write(self):
        script = snapshot_script([member(969, sha=OTHER_HEAD)], {})[0]
        code, transport = self.run_publish(script)
        self.assertEqual(code, 0)
        self.assertEqual(len(transport.calls), 1)
        self.assertEqual(self.post_calls(transport), [])
        for call in transport.calls:
            self.assertNotIn("/statuses", call.full_url)

    def test_unstable_snapshots_exit_1_with_no_status_read_or_write(self):
        edited = testlib.fixture_node("pr968", lastEditedAt="2026-11-12T13:00:00Z")
        dismissed = testlib.fixture_node("pr968", state="DISMISSED")
        unlisted = testlib.fixture_node("pr968", author={
            "__typename": "Bot", "login": "other[bot]", "databaseId": 123456})
        snapshots = [snapshot_script([member()], {968: [pass_node()]}),
                     snapshot_script([member()], {968: [edited]}),
                     snapshot_script([member()], {968: [dismissed]}),
                     snapshot_script([member()], {968: [unlisted]})]
        responses = []
        for responses_part, _ in snapshots:
            responses.extend(responses_part)
        code, transport = self.run_publish(responses)
        self.assertEqual(code, 1)
        self.assertEqual(len(transport.calls), 8)
        self.assertEqual(self.post_calls(transport), [])
        for call in transport.calls:
            self.assertNotIn("/statuses", call.full_url)


class SuppressionTest(PublishTestCase):
    """Suppression compares only the selected latest app status; an
    unchanged decision skips the POST entirely."""

    def test_unchanged_success_skips_the_post_and_exits_0(self):
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [FakeResponse(200, [status_record()])]))
        self.assertEqual(code, 0)
        self.assertEqual(self.post_calls(transport), [])
        self.assertEqual(len(transport.calls), 5)

    def test_unchanged_error_skips_the_post_and_still_exits_1(self):
        statuses = FakeResponse(200, [status_record(
            state="error", description=INVALID_INPUT_DESCRIPTION,
            target_url=PR968_URL)])
        code, transport = self.run_publish(publish_script(
            invalid_input_snapshot(), [statuses]))
        self.assertEqual(code, 1)
        self.assertEqual(self.post_calls(transport), [])

    def test_differing_app_status_is_replaced(self):
        statuses = FakeResponse(200, [status_record(description="stale summary")])
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [statuses], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        self.assertEqual(json.loads(posts[0].data), {
            "state": "success", "context": "bits-review/head",
            "description": PASS_DESCRIPTION, "target_url": PASS_REVIEW_URL})
        self.assert_write_tokens(transport)

    def test_non_app_status_is_never_selected_for_comparison(self):
        statuses = FakeResponse(200, [
            # Matches the decision in every compared field, but its creator
            # is not the gate's publisher app.
            status_record(creator=OTHER_CREATOR, status_id=900,
                           created_at="2026-11-12T13:00:00Z"),
            # The latest app status differs, so the write still happens.
            status_record(description="stale summary", status_id=50,
                          created_at="2026-11-12T11:00:00Z"),
        ])
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [statuses], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        self.assertEqual(json.loads(posts[0].data)["description"], PASS_DESCRIPTION)

    def test_failed_status_read_never_suppresses_the_write(self):
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [FakeResponse(404)], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        self.assertEqual(len(self.post_calls(transport)), 1)

    def test_every_status_page_is_read_before_selection(self):
        # Page 1 carries a stale app status; page 2 (through the Link
        # header) a newer matching one — suppression can only come from
        # reading every page.
        page2 = "%s/repos/%s/commits/%s/statuses?page=2" % (API, REPO, HEAD)
        first = FakeResponse(200, [status_record(
            description="stale summary", status_id=50,
            created_at="2026-11-12T11:00:00Z")],
            link='<%s>; rel="next"' % (page2,))
        second = FakeResponse(200, [status_record(
            status_id=200, created_at="2026-11-12T12:30:00Z")])
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [first, second]))
        self.assertEqual(code, 0)
        self.assertEqual(self.post_calls(transport), [])
        self.assertIn(page2, [call.full_url for call in transport.calls])

    def test_malformed_next_link_fails_the_status_read_closed_and_still_writes(self):
        # Page 1 carries a MATCHING app status plus a malformed second-page
        # Link header: a successful read would have suppressed, so the
        # single POST below is the fail-closed proof.
        shapes = (
            '<https://evil.example.test/repos/x>; rel="next"',
            '</repos/x?page=2>; rel="next"',
        )
        for link in shapes:
            with self.subTest(link=link):
                first = FakeResponse(200, [status_record()], link=link)
                code, transport = self.run_publish(publish_script(
                    pass_snapshot(), [first], FakeResponse(201, {})))
                self.assertEqual(code, 0)
                self.assertEqual(len(self.post_calls(transport)), 1)
                self.assertEqual([call.full_url for call in transport.calls].count(
                    statuses_read_url()), 1)
                self.assertNotIn("?page=2", " ".join(
                    call.full_url for call in transport.calls))
                self.assert_write_tokens(transport)

    def test_foreign_context_status_is_never_selected_for_comparison(self):
        # The newest app-creator status matches the decision in every
        # compared field but its context is foreign: it is not this gate's
        # output and must never suppress the write.
        statuses = FakeResponse(200, [
            status_record(context="some-other-context", status_id=900,
                          created_at="2026-11-12T13:00:00Z"),
        ])
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [statuses], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        self.assertEqual(json.loads(posts[0].data)["description"], PASS_DESCRIPTION)

    def test_malformed_app_status_is_never_selected_for_comparison(self):
        # A malformed app-creator entry that matches the decision in every
        # compared field is never selected for the suppression comparison:
        # the write still happens. With created_at=None, guard removal
        # would crash the comparison instead of suppressing.
        for bad in ("created_at", "id"):
            with self.subTest(bad=bad):
                first = status_record(status_id=900,
                                      created_at="2026-11-12T13:00:00Z")
                if bad == "created_at":
                    first["created_at"] = None
                else:
                    first["id"] = 0
                statuses = FakeResponse(200, [
                    first,
                    status_record(description="stale summary", status_id=50,
                                  created_at="2026-11-12T11:00:00Z"),
                ])
                code, transport = self.run_publish(publish_script(
                    pass_snapshot(), [statuses], FakeResponse(201, {})))
                self.assertEqual(code, 0)
                posts = self.post_calls(transport)
                self.assertEqual(len(posts), 1)
                self.assertEqual(json.loads(posts[0].data)["description"],
                                 PASS_DESCRIPTION)
                self.assert_write_tokens(transport)


class LatestSelectionTest(PublishTestCase):
    """Only the app status with the greatest (created_at, id) is selected
    for the comparison."""

    def test_greatest_created_at_wins_even_when_an_older_entry_matches(self):
        statuses = FakeResponse(200, [
            status_record(created_at="2026-11-12T12:00:00Z", status_id=100),
            status_record(description="newer different",
                          created_at="2026-11-12T13:00:00Z", status_id=101),
        ])
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [statuses], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        self.assertEqual(json.loads(posts[0].data)["description"], PASS_DESCRIPTION)

    def test_equal_created_at_is_broken_by_the_greater_id(self):
        statuses = FakeResponse(200, [
            status_record(status_id=100),
            status_record(status_id=101, description="same instant, higher id"),
        ])
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [statuses], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        self.assertEqual(len(self.post_calls(transport)), 1)


class StatusWriteTest(PublishTestCase):
    """The POST: payload from the policy, the explicit sha, and the exit
    code of every write branch."""

    def test_success_is_posted_only_from_the_all_pass_branch(self):
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        self.assertEqual(posts[0].get_method(), "POST")
        self.assertEqual(posts[0].full_url, status_post_url(HEAD))
        self.assertEqual(json.loads(posts[0].data), {
            "state": "success", "context": "bits-review/head",
            "description": PASS_DESCRIPTION, "target_url": PASS_REVIEW_URL})

    def test_fail_and_pending_decisions_never_post_success(self):
        fail = snapshot_script([member(985)], {985: [fail_node()]})
        code, transport = self.run_publish(publish_script(
            fail, [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        self.assertEqual(
            json.loads(self.post_calls(transport)[0].data)["state"], "failure")
        prs = [member(968), member(969)]
        reviews = {968: [pass_node()], 969: []}
        pending = snapshot_script(prs, reviews)
        code, transport = self.run_publish(publish_script(
            pending, [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        payload = json.loads(self.post_calls(transport)[0].data)
        self.assertEqual((payload["state"], payload["target_url"]),
                         ("pending", PR969_URL))

    def test_error_decision_is_posted_as_error_and_exits_1(self):
        code, transport = self.run_publish(publish_script(
            invalid_input_snapshot(), [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 1)
        payload = json.loads(self.post_calls(transport)[0].data)
        self.assertEqual(payload["state"], "error")
        self.assertEqual(payload["description"], INVALID_INPUT_DESCRIPTION)

    def test_member_less_error_omits_the_optional_fields_and_exits_1(self):
        code, transport = self.run_publish(publish_script(
            failed_pulls_script(), [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 1)
        payload = json.loads(self.post_calls(transport)[0].data)
        self.assertEqual(payload, {"state": "error", "context": "bits-review/head"})

    def test_failed_post_exits_1(self):
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [FakeResponse(200, [])], FakeResponse(404)))
        self.assertEqual(code, 1)
        self.assertEqual(len(self.post_calls(transport)), 1)

    def test_missing_status_token_exits_1_without_a_post(self):
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [FakeResponse(200, [])]),
            env=publish_env_without_status_token())
        self.assertEqual(code, 1)
        self.assertEqual(self.post_calls(transport), [])


class WriteTokenTest(PublishTestCase):
    """Every read carries GITHUB_TOKEN; the one POST carries STATUS_TOKEN
    and no read ever carries it."""

    def test_read_tokens_and_post_token_are_strictly_separated(self):
        code, transport = self.run_publish(publish_script(
            pass_snapshot(), [FakeResponse(200, [])], FakeResponse(201, {})))
        self.assertEqual(code, 0)
        self.assert_write_tokens(transport)
        posts = self.post_calls(transport)
        self.assertEqual(len(posts), 1)
        for value in posts[0].headers.values():
            self.assertNotIn(GITHUB_TOKEN, value)


class ExplicitShaTest(PublishTestCase):
    """The status read and the write target only the explicit --sha
    argument, never any other head."""

    def test_every_sha_bearing_url_uses_the_explicit_argument(self):
        snapshot = snapshot_script(
            [member(969, sha=OTHER_HEAD)],
            {969: [testlib.fixture_node("pr968", commit={"oid": OTHER_HEAD})]},
            head=OTHER_HEAD)
        code, transport = self.run_publish(publish_script(
            snapshot, [FakeResponse(200, [])], FakeResponse(201, {})),
            sha=OTHER_HEAD)
        self.assertEqual(code, 0)
        posts = self.post_calls(transport, sha=OTHER_HEAD)
        self.assertEqual(len(posts), 1)
        for call in transport.calls:
            if "/statuses" in call.full_url:
                self.assertIn(OTHER_HEAD, call.full_url)
                self.assertNotIn(HEAD, call.full_url)


if __name__ == "__main__":
    unittest.main()
