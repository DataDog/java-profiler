# Copyright 2026, Datadog, Inc.
"""Scaffold exercises and policy-core tests for the Bits review gate.

Holds the fixture-, builder- and mapping-behavior checks of the scaffold
plus the policy family's validation, scope, candidacy, outcome, decision
and fingerprint tests; the adapter and CLI families extend this module.
"""

import os
import re
import sys
import unittest

# The policy module lives in the parent directory, next to the gate script
# that ships it; discovery starts in this tests directory.
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import bits_review_gate_policy as policy  # noqa: E402

import bits_review_gate_testlib as testlib

PR985_HEAD = "1dcc3fa57582f2b595403f2b6a54e4464f352223"
PR968_HEAD = "1115eb583f475b62544d634bb12bf750ae913e04"


def fixture_record(pr):
    """A validated Bot record carrying a real Bits fixture body."""
    rest = testlib.load_review_fixture(pr)
    return testlib.build_review_record(
        id=rest["id"], author_id=rest["user"]["id"], author_login=rest["user"]["login"],
        state=rest["state"], body=rest["body"], commit_oid=rest["commit_id"],
        submitted_at=rest["submitted_at"])


def build_pr(number=985, sha=PR985_HEAD, base_ref="main", state="open"):
    """A REST pulls-list shaped PR record."""
    return {"number": number, "head": {"sha": sha}, "base": {"ref": base_ref}, "state": state}


REVIEWER_ID_COMMENT = "<!-- datadog-code-review reviewer-id=bad90057-5c12-4101-ad47-d91c9dff0f90 -->"
PROD_ENV_COMMENT = "<!-- datadog-autotest:v1:prod -->"
_FULL_COMMENT_RE = re.compile(r"<!--.*?-->", re.DOTALL)


def passing_record(**overrides):
    """A never-edited, allowlisted, valid PASS record bound to PR 968's head."""
    record = fixture_record("pr968")
    record.update(overrides)
    return record


def pass_body():
    """The real never-edited PASS fixture body."""
    return fixture_record("pr968")["body"]


def meta_comment(body):
    """The single autotest-meta comment of a body."""
    return [c for c in _FULL_COMMENT_RE.findall(body) if "autotest-meta" in c][0]


def drop_meta(body):
    return body.replace(meta_comment(body), "")


def drop_env(body):
    return body.replace(PROD_ENV_COMMENT, "")


def snapshot_records(head=PR968_HEAD):
    """Two normalized Bot records bound to head, ids 1 and 2."""
    return [
        testlib.build_review_record(id=1, author_id=88084959, commit_oid=head,
                                    body="first plain text", submitted_at="2026-11-12T09:00:00Z"),
        testlib.build_review_record(id=2, author_id=214633350, commit_oid=head,
                                    body=pass_body(), submitted_at="2026-11-12T10:00:00Z"),
    ]


def base_snapshot(head=PR968_HEAD):
    """A seam-shaped snapshot: two P(H) members sharing head, their
    normalized records and no error flags."""
    return {
        "sha": head,
        "prs": [testlib.build_pr_record(number=968, sha=head),
                testlib.build_pr_record(number=985, sha=head)],
        "reviews": {968: snapshot_records(head),
                    985: [testlib.build_review_record(id=3, commit_oid=head, body="LGTM")]},
        "api_error": [],
        "invalid_input": [],
        "outcomes": {968: "pass", 985: "missing"},
    }


class FixtureLoadingTest(unittest.TestCase):
    """Each fixture file loads and supplies the real REST review values."""

    def test_pr985_fixture_supplies_real_review_values(self):
        rest = testlib.load_review_fixture("pr985")
        self.assertEqual(rest["id"], 5872953227)
        self.assertEqual(rest["commit_id"], "1dcc3fa57582f2b595403f2b6a54e4464f352223")
        self.assertEqual(rest["user"]["id"], 214633350)
        self.assertEqual(rest["user"]["type"], "Bot")
        self.assertEqual(rest["user"]["login"], "datadog-official[bot]")
        self.assertEqual(rest["submitted_at"], "2026-11-12T10:38:09Z")
        self.assertEqual(rest["state"], "COMMENTED")
        self.assertIn("verdict=FAIL", rest["body"])
        self.assertIn("autotest-meta", rest["body"])

    def test_pr968_fixture_supplies_real_review_values(self):
        rest = testlib.load_review_fixture("pr968")
        self.assertEqual(rest["id"], 5872101609)
        self.assertEqual(rest["commit_id"], "1115eb583f475b62544d634bb12bf750ae913e04")
        self.assertEqual(rest["user"]["id"], 88084959)
        self.assertEqual(rest["user"]["type"], "Bot")
        self.assertEqual(rest["user"]["login"], "datadog-datadog-prod-us1[bot]")
        self.assertEqual(rest["submitted_at"], "2026-11-12T09:30:55Z")
        self.assertEqual(rest["state"], "COMMENTED")
        self.assertIn("verdict=PASS", rest["body"])
        self.assertIn("autotest-meta", rest["body"])


class BuilderContractTest(unittest.TestCase):
    """Builders emit exactly the contract's node and record fields."""

    def test_node_builder_emits_exactly_contract_node_fields(self):
        node = testlib.build_review_node()
        self.assertEqual(set(node), {"databaseId", "state", "body", "submittedAt", "lastEditedAt", "commit", "author"})
        self.assertEqual(set(node["commit"]), {"oid"})
        self.assertEqual(set(node["author"]), {"__typename", "login", "databaseId"})
        self.assertEqual(testlib.build_review_node(databaseId=7)["databaseId"], 7)

    def test_record_builder_emits_exactly_contract_record_fields(self):
        record = testlib.build_review_record()
        self.assertEqual(set(record), {"id", "author_typename", "author_id", "author_login", "state", "body", "commit_oid", "submitted_at", "last_edited_at"})
        self.assertEqual(testlib.build_review_record(state="APPROVED")["state"], "APPROVED")


class RestToNodeMappingTest(unittest.TestCase):
    """The REST-fixture to GraphQL-node mapping preserves fixture data."""

    def test_mapping_carries_each_fixture_field(self):
        for rest in testlib.load_review_fixtures():
            with self.subTest(id=rest["id"]):
                node = testlib.rest_review_to_node(rest)
                self.assertEqual(node["databaseId"], rest["id"])
                self.assertEqual(node["state"], rest["state"])
                self.assertEqual(node["submittedAt"], rest["submitted_at"])
                self.assertEqual(node["commit"]["oid"], rest["commit_id"])
                self.assertEqual(node["author"]["databaseId"], rest["user"]["id"])
                self.assertEqual(node["author"]["__typename"], rest["user"]["type"])
                self.assertEqual(node["author"]["login"], rest["user"]["login"])

    def test_mapping_round_trips_fixture_bodies_byte_identically(self):
        for rest in testlib.load_review_fixtures():
            with self.subTest(id=rest["id"]):
                node = testlib.rest_review_to_node(rest)
                self.assertEqual(node["body"], rest["body"])
                self.assertIn("verdict=", node["body"])
                self.assertIsNone(node["lastEditedAt"])


class MarkedTest(unittest.TestCase):
    """The three marker substrings each mark a body on their own."""

    def test_each_marker_substring_alone_marks_the_body(self):
        for marker in ("autotest-meta", "datadog-code-review", "datadog-autotest"):
            with self.subTest(marker=marker):
                self.assertTrue(policy.is_marked("looks human <!-- %s --> done" % marker))
        self.assertFalse(policy.is_marked("plain review text"))
        self.assertFalse(policy.is_marked(None))


class EditedStateTest(unittest.TestCase):
    """Edit state derives from the raw last_edited_at value only."""

    def test_raw_last_edited_value_is_retained_and_marks_edited(self):
        record = testlib.build_review_record(last_edited_at="2026-11-12T11:00:00Z")
        self.assertTrue(policy.is_edited(record))
        self.assertEqual(record["last_edited_at"], "2026-11-12T11:00:00Z")

    def test_null_last_edited_is_not_edited(self):
        record = testlib.build_review_record()
        self.assertFalse(policy.is_edited(record))
        self.assertIsNone(record["last_edited_at"])


class ScopeTest(unittest.TestCase):
    """Scope binds to the exact 40-lowercase-hex head only."""

    def test_fixture_record_is_in_scope_for_its_own_head(self):
        self.assertTrue(policy.is_in_scope(fixture_record("pr985"), PR985_HEAD))
        self.assertTrue(policy.is_in_scope(fixture_record("pr968"), PR968_HEAD))

    def test_head_variants_are_out_of_scope(self):
        record = fixture_record("pr985")
        for head in (PR985_HEAD[:-1], PR985_HEAD + "a", PR985_HEAD.upper(), "2" + PR985_HEAD[1:], "0" * 40):
            with self.subTest(head=head):
                self.assertFalse(policy.is_in_scope(record, head))

    def test_null_commit_pending_and_null_submitted_are_out_of_scope(self):
        self.assertFalse(policy.is_in_scope(testlib.build_review_record(commit_oid=None), PR985_HEAD))
        self.assertFalse(policy.is_in_scope(testlib.build_review_record(commit_oid=PR985_HEAD, state="PENDING"), PR985_HEAD))
        self.assertFalse(policy.is_in_scope(testlib.build_review_record(commit_oid=PR985_HEAD, submitted_at=None), PR985_HEAD))

class CandidateTest(unittest.TestCase):
    """Candidates are exactly the marked or edited Bot reviews."""

    def test_marked_and_edited_bot_reviews_are_candidates(self):
        marked = testlib.build_review_record(body=fixture_record("pr968")["body"])
        edited = testlib.build_review_record(last_edited_at="2026-11-12T11:00:00Z")
        self.assertTrue(policy.is_candidate(marked))
        self.assertTrue(policy.is_candidate(edited))
        self.assertTrue(policy.is_candidate(fixture_record("pr985")))

    def test_user_copied_markers_are_not_candidates(self):
        record = fixture_record("pr985")
        record["author_typename"] = "User"
        self.assertTrue(policy.is_marked(record["body"]))
        self.assertFalse(policy.is_candidate(record))

    def test_allowlisted_unedited_unmarked_bot_is_not_a_candidate(self):
        record = testlib.build_review_record(author_id=214633350, author_login="datadog-official[bot]", body="LGTM")
        self.assertFalse(policy.is_candidate(record))


class ReviewValidationFailureTest(unittest.TestCase):
    """Every contract failure shape fails with its own field token."""

    def test_invalid_shapes_fail_with_their_token(self):
        marked_body = fixture_record("pr985")["body"]
        cases = [
            ("body", {"body": 123}), ("last_edited_at", {"last_edited_at": "not-a-timestamp"}),
            ("last_edited_at", {"last_edited_at": 17}), ("id", {"id": 0}),
            ("id", {"id": -3}), ("id", {"id": "5872953227"}),
            ("id", {"id": True}), ("state", {"state": "CHANGED_REQUESTED"}),
            ("state", {"state": "open"}), ("state", {"state": None}),
            ("commit_oid", {"commit_oid": PR985_HEAD[:-1]}), ("commit_oid", {"commit_oid": PR985_HEAD.upper()}),
            ("commit_oid", {"commit_oid": "z" * 40}), ("submitted_at", {"submitted_at": None}),
            ("submitted_at", {"submitted_at": "garbage"}), ("author_id", {"author_id": 0}),
            ("author_id", {"author_id": None}),
            ("author_typename", {"author_typename": None, "body": marked_body}),
            ("author_typename", {"author_typename": "Organization", "body": marked_body}),
            ("author_typename", {"author_typename": "Mannequin", "last_edited_at": "2026-11-12T11:00:00Z"}),
        ]
        for reason, overrides in cases:
            with self.subTest(reason=reason, overrides=overrides):
                record = testlib.build_review_record(**overrides)
                self.assertEqual(policy.validate_review_record(record), reason)

    def test_user_record_is_ignored_without_further_checks(self):
        record = testlib.build_review_record(
            author_typename="User", author_id=0, body=123, id=-1,
            state="garbage", commit_oid="zz", submitted_at="nope")
        self.assertIsNone(policy.validate_review_record(record))

    def test_unmarked_null_author_record_is_not_a_validation_failure(self):
        record = testlib.build_review_record(author_typename=None, author_id=None, body="plain text")
        self.assertIsNone(policy.validate_review_record(record))


class ReviewValidationPassTest(unittest.TestCase):
    """Valid records pass, including both timestamp spellings."""

    def test_every_review_state_is_valid(self):
        for state in policy.REVIEW_STATES:
            with self.subTest(state=state):
                record = testlib.build_review_record(
                    state=state,
                    submitted_at=None if state == "PENDING" else "2026-11-12T09:30:55Z")
                self.assertIsNone(policy.validate_review_record(record))

    def test_offset_and_pending_with_submitted_at_are_valid(self):
        offset = testlib.build_review_record(submitted_at="2026-11-12T11:30:55+02:00")
        pending = testlib.build_review_record(state="PENDING")
        self.assertIsNone(policy.validate_review_record(offset))
        self.assertIsNone(policy.validate_review_record(pending))

    def test_fixture_derived_records_are_valid_marked_candidates(self):
        for pr in ("pr985", "pr968"):
            with self.subTest(pr=pr):
                record = fixture_record(pr)
                self.assertIsNone(policy.validate_review_record(record))
                self.assertTrue(policy.is_marked(record["body"]))
                self.assertTrue(policy.is_candidate(record))
                self.assertFalse(policy.is_edited(record))


class PrValidationTest(unittest.TestCase):
    """PR records must carry the contract's required fields."""

    def test_valid_pr_record_passes(self):
        self.assertIsNone(policy.validate_pr_record(build_pr()))
        self.assertIsNone(policy.validate_pr_record(build_pr(number=968, sha=PR968_HEAD, state="open")))

    def test_pr_field_failures(self):
        cases = [
            ("number", build_pr(number=0)), ("number", build_pr(number=-1)),
            ("number", build_pr(number="985")), ("number", build_pr(number=True)),
            ("head.sha", build_pr(sha=PR985_HEAD[:-1])), ("head.sha", build_pr(sha=PR985_HEAD.upper())),
            ("head.sha", build_pr(sha=None)),
            ("head.sha", {"number": 985, "base": {"ref": "main"}, "state": "open"}),
            ("base.ref", build_pr(base_ref=7)),
            ("base.ref", {"number": 985, "head": {"sha": PR985_HEAD}, "state": "open"}),
            ("state", build_pr(state=None)), ("state", build_pr(state=5)),
        ]
        for reason, pr in cases:
            with self.subTest(reason=reason, pr=pr):
                self.assertEqual(policy.validate_pr_record(pr), reason)


class LatestSelectionTest(unittest.TestCase):
    """Latest selection orders by parsed UTC instant, then id, and never
    consults dismissal, origin, edit or marker state."""

    def test_equal_timestamps_break_the_tie_by_the_higher_id(self):
        fail = passing_record(id=1, body=fixture_record("pr985")["body"])
        newer_pass = passing_record(id=2)
        self.assertEqual(policy.outcome([fail, newer_pass], head=PR968_HEAD), "pass")
        self.assertEqual(policy.outcome([newer_pass, fail], head=PR968_HEAD), "pass")
        self.assertIs(policy.latest_candidate([fail, newer_pass], PR968_HEAD), newer_pass)

    def test_shuffled_input_keeps_the_selection(self):
        oldest = passing_record(id=1, submitted_at="2026-11-12T08:00:00Z")
        middle = passing_record(id=2, submitted_at="2026-11-12T09:00:00Z", state="DISMISSED")
        newest = passing_record(id=3, submitted_at="2026-11-12T10:00:00Z")
        for order in ([oldest, middle, newest], [newest, middle, oldest],
                      [middle, newest, oldest], [newest, oldest, middle]):
            with self.subTest(order=[r["id"] for r in order]):
                self.assertEqual(policy.outcome(order, head=PR968_HEAD), "pass")
                self.assertIs(policy.latest_candidate(order, PR968_HEAD), newest)

    def test_invalid_id_ties_break_deterministically(self):
        # Both records stay marked candidates with equal submitted_at; only
        # their ids are invalid, so the canonical JSON member form decides.
        first = passing_record(id="985-bad")
        second = passing_record(id=None)
        # None serializes after "985-bad" in the canonical member JSON, so
        # the second record is the deterministic winner.
        reference = policy.latest_candidate([first, second], PR968_HEAD)
        self.assertIsNotNone(reference)
        self.assertIs(reference, second)
        for order in ([first, second], [second, first]):
            with self.subTest(order=[repr(r["id"]) for r in order]):
                self.assertIs(policy.latest_candidate(order, PR968_HEAD), reference)

    def test_equivalent_timestamp_spellings_compare_as_utc_instants(self):
        # 09:00+05:00 is 04:00 UTC: lexically greater, instant-earlier.
        lexical_trap = passing_record(
            id=5, submitted_at="2026-11-12T09:00:00+05:00", body=fixture_record("pr985")["body"])
        half_past = passing_record(id=2, submitted_at="2026-11-12T04:30:00Z")
        self.assertEqual(policy.outcome([lexical_trap, half_past], head=PR968_HEAD), "pass")
        z = passing_record(id=3, submitted_at="2026-11-12T10:00:00Z", body=fixture_record("pr985")["body"])
        offset = passing_record(id=4, submitted_at="2026-11-12T12:00:00+02:00")
        naive = passing_record(id=1, submitted_at="2026-11-12T10:00:00")
        self.assertEqual(policy.outcome([z, offset, naive], head=PR968_HEAD), "pass")
        self.assertIs(policy.latest_candidate([z, offset, naive], PR968_HEAD), offset)

    def test_an_edit_to_an_older_review_does_not_reorder_it(self):
        older_edited = passing_record(
            id=1, submitted_at="2026-11-12T08:00:00Z", last_edited_at="2026-11-12T13:00:00Z")
        newer_pass = passing_record(id=2)
        self.assertEqual(policy.outcome([older_edited, newer_pass], head=PR968_HEAD), "pass")
        self.assertIs(policy.latest_candidate([older_edited, newer_pass], PR968_HEAD), newer_pass)

    def test_out_of_scope_records_never_win_the_selection(self):
        other_head = passing_record(id=7, submitted_at="2026-11-12T15:00:00Z", commit_oid=PR985_HEAD)
        pending = passing_record(id=8, submitted_at="2026-11-12T15:30:00Z", state="PENDING")
        null_commit = passing_record(id=9, submitted_at="2026-11-12T16:00:00Z", commit_oid=None)
        valid_pass = passing_record(id=2)
        records = [other_head, pending, null_commit, valid_pass]
        self.assertEqual(policy.outcome(records, head=PR968_HEAD), "pass")
        self.assertIs(policy.latest_candidate(records, PR968_HEAD), valid_pass)


class BindingReasonsTest(unittest.TestCase):
    """The contract's binding expected-reasons table."""

    def test_unlisted_bot_edited_markerless_is_untrusted_origin(self):
        record = passing_record(author_id=421337, body="plain bot text",
                                last_edited_at="2026-11-12T11:00:00Z")
        self.assertEqual(policy.outcome([record], head=PR968_HEAD), "untrusted-origin")

    def test_unlisted_bot_marked_pass_is_untrusted_origin(self):
        record = passing_record(author_id=421337)
        self.assertEqual(policy.outcome([record], head=PR968_HEAD), "untrusted-origin")

    def test_allowlisted_edited_markerless_is_edited_summary(self):
        record = passing_record(body="plain bot text", last_edited_at="2026-11-12T11:00:00Z")
        self.assertEqual(policy.outcome([record], head=PR968_HEAD), "edited-summary")

    def test_allowlisted_edited_valid_pass_body_is_edited_summary(self):
        record = passing_record(last_edited_at="2026-11-12T11:00:00Z")
        self.assertEqual(policy.outcome([record], head=PR968_HEAD), "edited-summary")

    def test_allowlisted_dismissed_and_edited_is_dismissed(self):
        record = passing_record(state="DISMISSED", last_edited_at="2026-11-12T11:00:00Z")
        self.assertEqual(policy.outcome([record], head=PR968_HEAD), "dismissed")

    def test_each_of_the_eight_allowlisted_ids_passes_by_outcome(self):
        for author_id in (214633350, 88084959, 261164178, 298424163,
                          266080212, 266080418, 266081015, 266788760):
            with self.subTest(author_id=author_id):
                record = passing_record(author_id=author_id)
                self.assertIsNone(record["last_edited_at"])
                self.assertEqual(policy.outcome([record], head=PR968_HEAD), "pass")
        adjacent = passing_record(author_id=214633351)
        self.assertEqual(policy.outcome([adjacent], head=PR968_HEAD), "untrusted-origin")


class NoFallbackTest(unittest.TestCase):
    """A bad latest candidate never uncovers an older PASS."""

    def setUp(self):
        self.older_pass = passing_record(id=1, submitted_at="2026-11-12T08:00:00Z")

    def _latest(self, **overrides):
        return passing_record(id=2, submitted_at="2026-11-12T12:00:00Z", **overrides)

    def test_latest_dismissed_does_not_fall_back(self):
        records = [self.older_pass, self._latest(state="DISMISSED")]
        self.assertEqual(policy.outcome(records, head=PR968_HEAD), "dismissed")

    def test_latest_edited_does_not_fall_back(self):
        records = [self.older_pass, self._latest(last_edited_at="2026-11-12T13:00:00Z")]
        self.assertEqual(policy.outcome(records, head=PR968_HEAD), "edited-summary")

    def test_latest_malformed_does_not_fall_back(self):
        records = [self.older_pass, self._latest(body=drop_meta(pass_body()))]
        self.assertEqual(policy.outcome(records, head=PR968_HEAD), "malformed:missing-meta")

    def test_latest_untrusted_does_not_fall_back(self):
        records = [self.older_pass, self._latest(author_id=421337)]
        self.assertEqual(policy.outcome(records, head=PR968_HEAD), "untrusted-origin")

    def test_a_newer_never_edited_pass_clears_an_older_edited_block(self):
        older_edited = passing_record(
            id=1, submitted_at="2026-11-12T08:00:00Z", last_edited_at="2026-11-12T13:00:00Z")
        self.assertEqual(policy.outcome([older_edited, self._latest()], head=PR968_HEAD), "pass")


class MalformedMarkerTest(unittest.TestCase):
    """Every malformed:<sub> reason is reached from the real PASS body."""

    def _outcome_for_body(self, body):
        self.assertEqual(policy.outcome([passing_record(body=body)], head=PR968_HEAD), "malformed:%s" % self.sub_reason)

    def test_missing_meta(self):
        self.sub_reason = "missing-meta"
        self._outcome_for_body(drop_meta(pass_body()))
        two_metes = pass_body() + "\n<!-- autotest-meta verdict=FAIL -->"
        self._outcome_for_body(two_metes)

    def test_conflicting_verdict(self):
        self.sub_reason = "conflicting-verdict"
        self._outcome_for_body(pass_body().replace("verdict=PASS", "verdict=PASS verdict=FAIL", 1))

    def test_unknown_verdict(self):
        self.sub_reason = "unknown-verdict"
        for replacement in ("verdict=WIBBLE", "verdict=pass", "verdict=FAIL,", "verdict="):
            with self.subTest(replacement=replacement):
                self._outcome_for_body(pass_body().replace("verdict=PASS", replacement, 1))
        self._outcome_for_body(pass_body().replace("verdict=PASS ", "", 1))

    def test_reviewer_id(self):
        self.sub_reason = "reviewer-id"
        self._outcome_for_body(pass_body().replace(REVIEWER_ID_COMMENT, ""))
        self._outcome_for_body(pass_body() + "\n" + REVIEWER_ID_COMMENT)
        wrong_id = REVIEWER_ID_COMMENT.replace("bad90057", "bad90058")
        self._outcome_for_body(pass_body().replace(REVIEWER_ID_COMMENT, wrong_id))

    def test_env_marker(self):
        self.sub_reason = "env-marker"
        self._outcome_for_body(drop_env(pass_body()))
        staging = pass_body().replace(PROD_ENV_COMMENT, "<!-- datadog-autotest:v1:staging -->")
        self._outcome_for_body(staging)
        self._outcome_for_body(pass_body() + "\n" + PROD_ENV_COMMENT)

    def test_sub_reasons_follow_the_contract_order(self):
        # meta before verdict: both wrong reports missing-meta
        self.sub_reason = "missing-meta"
        self._outcome_for_body(drop_env(drop_meta(pass_body())))
        # verdict before reviewer-id
        self.sub_reason = "unknown-verdict"
        self._outcome_for_body(
            pass_body().replace("verdict=PASS", "verdict=MAYBE", 1).replace(REVIEWER_ID_COMMENT, ""))
        # reviewer-id before env
        self.sub_reason = "reviewer-id"
        self._outcome_for_body(
            pass_body().replace(REVIEWER_ID_COMMENT, "").replace(PROD_ENV_COMMENT,
                "<!-- datadog-autotest:v1:staging -->"))

    def test_badges_image_text_and_delivery_markers_are_ignored(self):
        badge_flipped = pass_body().replace("BITS%20CODE%20REVIEW-PASS", "BITS%20CODE%20REVIEW-FAIL", 1)
        badge_flipped = badge_flipped.replace("Bits Code Review: PASS", "Bits Code Review: FAIL", 1)
        self._assert_pass(badge_flipped)
        delivery_retagged = pass_body().replace(
            "datadog-autotest-delivery:v1:prod:", "datadog-autotest-delivery:v1:staging:", 1)
        self._assert_pass(delivery_retagged)

    def _assert_pass(self, body):
        self.assertIn("verdict=PASS", meta_comment(body))
        self.assertEqual(policy.outcome([passing_record(body=body)], head=PR968_HEAD), "pass")


class InvalidInputPrecedenceTest(unittest.TestCase):
    """Rule 1: a possible candidate that failed validation wins wherever it
    sits in the order, and unrelated invalid reviews never block."""

    def test_invalid_possible_candidate_at_any_position(self):
        valid_pass = passing_record(id=2, submitted_at="2026-11-12T12:00:00Z")
        oldest = passing_record(id=1, submitted_at="2026-11-12T08:00:00Z", state="garbage")
        middle = passing_record(id=3, submitted_at="2026-11-12T10:00:00Z", body=123)
        newest = passing_record(id=4, submitted_at="2026-11-12T15:00:00Z",
                                last_edited_at="whenever")
        broken_by_position = {"oldest": oldest, "middle": middle, "newest": newest}
        for name, broken in broken_by_position.items():
            with self.subTest(position=name):
                self.assertEqual(policy.outcome([valid_pass, broken], head=PR968_HEAD), "invalid-input")
        self.assertEqual(policy.outcome([oldest, middle, newest], head=PR968_HEAD), "invalid-input")

    def test_invalid_input_beats_every_later_rule(self):
        latest_edited_untrusted = passing_record(
            id=9, submitted_at="2026-11-12T16:00:00Z", author_id=421337, body="plain",
            last_edited_at="2026-11-12T16:30:00Z")
        broken = passing_record(id=1, submitted_at="2026-11-12T07:00:00Z",
                                last_edited_at="not-parseable")
        records = [latest_edited_untrusted, broken]
        self.assertEqual(policy.outcome(records, head=PR968_HEAD), "invalid-input")

    def test_unrelated_invalid_bot_reviews_do_not_block(self):
        valid_pass = passing_record(id=2, submitted_at="2026-11-12T12:00:00Z")
        unrelated = passing_record(id=5, submitted_at="2026-11-12T15:00:00Z",
                                   body="LGTM", state="garbage")
        unmarked_null_author = passing_record(
            id=6, submitted_at="2026-11-12T15:30:00Z", body="LGTM",
            author_typename=None, author_id=None)
        records = [valid_pass, unrelated, unmarked_null_author]
        self.assertEqual(policy.outcome(records, head=PR968_HEAD), "pass")

    def test_api_error_is_reported_before_any_rule(self):
        record = passing_record()
        broken = passing_record(id=1, body=123)
        self.assertEqual(policy.outcome([record, broken], head=PR968_HEAD, api_error=True), "api-error")
        self.assertEqual(policy.outcome([], head=PR968_HEAD, api_error=True), "api-error")


class MissingOutcomeTest(unittest.TestCase):
    """Rule 2: no in-scope candidate means missing."""

    def test_empty_and_non_candidate_records_are_missing(self):
        self.assertEqual(policy.outcome([], head=PR968_HEAD), "missing")
        self.assertEqual(policy.outcome([passing_record(body="LGTM")], head=PR968_HEAD), "missing")
        self.assertEqual(policy.outcome([passing_record(state="PENDING")], head=PR968_HEAD), "missing")
        self.assertEqual(policy.outcome([passing_record(commit_oid=None)], head=PR968_HEAD), "missing")

    def test_wrong_head_shapes_are_missing(self):
        for head in (PR968_HEAD[:-1], PR968_HEAD.upper(), "2" + PR968_HEAD[1:], PR985_HEAD, None):
            with self.subTest(head=head):
                self.assertEqual(policy.outcome([passing_record()], head=head), "missing")

    def test_none_head_scopes_selection_to_empty(self):
        self.assertIsNone(policy.latest_candidate([passing_record()], head=None))


class FixtureOutcomeTest(unittest.TestCase):
    """The two supplied fixture reviews yield their binding outcomes."""

    def test_pr985_fails_and_pr968_passes_on_their_own_heads(self):
        self.assertEqual(policy.outcome([fixture_record("pr985")], head=PR985_HEAD), "fail")
        self.assertEqual(policy.outcome([fixture_record("pr968")], head=PR968_HEAD), "pass")

    def test_each_fixture_is_missing_for_the_other_head(self):
        self.assertEqual(policy.outcome([fixture_record("pr985")], head=PR968_HEAD), "missing")
        self.assertEqual(policy.outcome([fixture_record("pr968")], head=PR985_HEAD), "missing")


class OutcomeStateMappingTest(unittest.TestCase):
    """The contract's outcome-to-state mapping, verbatim."""

    def test_every_outcome_token_maps_to_its_state(self):
        cases = [
            ("pass", "success"), ("fail", "failure"), ("dismissed", "failure"),
            ("untrusted-origin", "failure"), ("edited-summary", "failure"),
            ("missing", "pending"), ("api-error", "error"), ("invalid-input", "error"),
        ]
        for token, state in cases:
            with self.subTest(token=token):
                self.assertEqual(policy.outcome_state(token), state)

    def test_every_malformed_sub_reason_is_failure(self):
        for token in ("malformed:missing-meta", "malformed:conflicting-verdict",
                      "malformed:unknown-verdict", "malformed:reviewer-id",
                      "malformed:env-marker", "malformed:anything-else"):
            with self.subTest(token=token):
                self.assertEqual(policy.outcome_state(token), "failure")

    def test_unknown_outcome_token_is_a_caller_bug(self):
        for token in ("garbage", "PASS", "", "malformed", None, 5):
            with self.subTest(token=token):
                with self.assertRaises(ValueError):
                    policy.outcome_state(token)


class DecideTest(unittest.TestCase):
    """The per-SHA conjunction: independent per-PR outcomes, severity
    error > failure > pending > success, lowest PR number on ties."""

    def test_pass_and_missing_is_pending_naming_the_pr_without_a_review(self):
        decision = policy.decide({968: "pass", 985: "missing"})
        self.assertEqual(decision, {"state": "pending", "reason": "missing", "governing_pr": 985})

    def test_pass_and_fail_is_failure_governed_by_the_failing_pr(self):
        decision = policy.decide({968: "pass", 985: "fail"})
        self.assertEqual(decision, {"state": "failure", "reason": "fail", "governing_pr": 985})

    def test_failure_outranks_pending_across_prs(self):
        decision = policy.decide({968: "fail", 985: "missing"})
        self.assertEqual(decision, {"state": "failure", "reason": "fail", "governing_pr": 968})
        mirrored = policy.decide({968: "missing", 985: "fail"})
        self.assertEqual(mirrored, {"state": "failure", "reason": "fail", "governing_pr": 985})

    def test_invalid_input_or_api_error_anywhere_is_error(self):
        for token in ("invalid-input", "api-error"):
            with self.subTest(token=token):
                decision = policy.decide({968: "pass", 985: token})
                self.assertEqual(decision["state"], "error")
                self.assertEqual(decision["reason"], token)
                # error dominates failure as well as pending and success
                dominating = policy.decide({5: "fail", 7: token})
                self.assertEqual(dominating,
                                 {"state": "error", "reason": token, "governing_pr": 7})

    def test_success_happens_only_on_the_all_pass_branch(self):
        self.assertEqual(policy.decide({5: "pass", 7: "pass", 9: "pass"}),
                         {"state": "success", "reason": "pass", "governing_pr": 5})
        for token in ("fail", "dismissed", "untrusted-origin", "edited-summary",
                      "malformed:missing-meta", "missing", "api-error", "invalid-input"):
            with self.subTest(token=token):
                decision = policy.decide({5: "pass", 7: token})
                self.assertNotEqual(decision["state"], "success")
                self.assertEqual(decision["state"], policy.outcome_state(token))

    def test_equal_severity_is_governed_by_the_lowest_pr_number(self):
        decision = policy.decide({10: "fail", 3: "edited-summary"})
        self.assertEqual(decision, {"state": "failure", "reason": "edited-summary", "governing_pr": 3})
        both_missing = policy.decide({12: "missing", 4: "missing"})
        self.assertEqual(both_missing, {"state": "pending", "reason": "missing", "governing_pr": 4})
        both_pass = policy.decide({12: "pass", 4: "pass"})
        self.assertEqual(both_pass["governing_pr"], 4)

    def test_each_pr_is_judged_on_its_own_reviews_only(self):
        head = PR968_HEAD
        pr968_records = [fixture_record("pr968")]
        pr985_fail_record = fixture_record("pr985")
        pr985_fail_record["commit_oid"] = head
        pr985_fail = [pr985_fail_record]
        self.assertEqual(policy.outcome(pr968_records, head=head), "pass")
        self.assertEqual(policy.outcome(pr985_fail, head=head), "fail")
        decision = policy.decide({968: "pass", 985: "fail"})
        self.assertEqual(
            decision, {"state": "failure", "reason": "fail", "governing_pr": 985})
        # a PASS on one shared-head PR never clears another PR's block
        pending = policy.decide({968: "pass", 985: "missing"})
        self.assertEqual(pending["state"], "pending")
        self.assertEqual(pending["governing_pr"], 985)

    def test_an_empty_p_h_is_never_a_decision(self):
        self.assertIsNone(policy.decide({}))

    def test_caller_contract_violations_raise(self):
        for bad in ({0: "pass"}, {"5": "pass"}, {True: "pass"}, {1: "garbage"}):
            with self.subTest(per_pr_outcomes=bad):
                with self.assertRaises(ValueError):
                    policy.decide(bad)


class DescribeTest(unittest.TestCase):
    """`Bits review <reason> on PR #<n>[: <detail>]`, capped at 140."""

    def test_description_shape_with_and_without_detail(self):
        self.assertEqual(policy.describe("missing", 985), "Bits review missing on PR #985")
        self.assertEqual(policy.describe("malformed:missing-meta", 968),
                         "Bits review malformed:missing-meta on PR #968")
        self.assertEqual(policy.describe("api-error", 12, "pulls"),
                         "Bits review api-error on PR #12: pulls")
        self.assertEqual(policy.describe("pass", 985, ""), "Bits review pass on PR #985")

    def test_description_is_capped_at_140_characters(self):
        long_detail = "d" * 300
        capped = policy.describe("missing", 985, long_detail)
        self.assertEqual(len(capped), 140)
        self.assertTrue(capped.startswith("Bits review missing on PR #985: "))
        huge_reason = "r" * 200
        self.assertEqual(len(policy.describe(huge_reason, 985)), 140)
        self.assertEqual(len(policy.describe("fail", 1, "x" * 132)), 140)

    def test_caller_contract_violations_raise(self):
        for bad_reason, bad_number, bad_detail in (
                (123, 985, None), (None, 985, None), ("pass", 0, None),
                ("pass", "985", None), ("pass", -1, None), ("pass", 985, 7)):
            with self.subTest(bad=(bad_reason, bad_number, bad_detail)):
                with self.assertRaises(ValueError):
                    policy.describe(bad_reason, bad_number, bad_detail)


class TargetUrlTest(unittest.TestCase):
    """The governing review's URL when a review governs, else the PR URL;
    both are built from API numbers only."""

    def test_both_url_shapes(self):
        review_url = policy.target_url("DataDog/java-profiler", 968, 5872101609)
        self.assertEqual(review_url,
                         "https://github.com/DataDog/java-profiler/pull/968#pullrequestreview-5872101609")
        pr_url = policy.target_url("DataDog/java-profiler", 968)
        self.assertEqual(pr_url, "https://github.com/DataDog/java-profiler/pull/968")
        self.assertNotIn("pullrequestreview", pr_url)

    def test_urls_are_built_from_api_numbers_only(self):
        self.assertEqual(policy.target_url("o/p", 7, 9),
                         "https://github.com/o/p/pull/7#pullrequestreview-9")
        self.assertEqual(policy.STATUS_CONTEXT, "bits-review/head")

    def test_caller_contract_violations_raise(self):
        for repo, number, review_id in (
                ("", 968, None), (None, 968, None), ("o/p", 0, None),
                ("o/p", "968", None), ("o/p", 968, 0), ("o/p", 968, -1),
                ("o/p", 968, "5872101609")):
            with self.subTest(args=(repo, number, review_id)):
                with self.assertRaises(ValueError):
                    policy.target_url(repo, number, review_id)


class FingerprintStabilityTest(unittest.TestCase):
    """The fingerprint is byte-stable when nothing changed and canonical:
    input ordering and derived outcomes never reach the digest."""

    def test_identical_snapshots_hash_identically(self):
        self.assertEqual(policy.fingerprint(base_snapshot()), policy.fingerprint(base_snapshot()))
        first, second = base_snapshot(), base_snapshot()
        self.assertIsNot(first, second)
        self.assertEqual(policy.fingerprint(first), policy.fingerprint(second))

    def test_record_and_member_ordering_never_reaches_the_digest(self):
        base = base_snapshot()
        reordered = base_snapshot()
        reordered["reviews"][968] = list(reversed(reordered["reviews"][968]))
        reordered["prs"] = list(reversed(reordered["prs"]))
        self.assertNotEqual(base["prs"][0]["number"], reordered["prs"][0]["number"])
        self.assertEqual(policy.fingerprint(base), policy.fingerprint(reordered))

    def test_invalid_entry_ordering_never_reaches_the_digest(self):
        # Invalid PR numbers and record ids share one sort bucket; the
        # bucket must canonically self-order so input order never reaches
        # the digest.
        base = base_snapshot()
        base["reviews"][985] = [
            testlib.build_review_record(id="bad-two", commit_oid=PR968_HEAD, body="LGTM two"),
            testlib.build_review_record(id=None, commit_oid=PR968_HEAD, body="LGTM one"),
        ]
        base["prs"] = [
            testlib.build_pr_record(number=None, sha=PR968_HEAD),
            testlib.build_pr_record(number="not-a-number", sha=PR985_HEAD),
        ]
        reordered = base_snapshot()
        reordered["reviews"][985] = list(reversed(base["reviews"][985]))
        reordered["prs"] = list(reversed(base["prs"]))
        self.assertEqual(policy.fingerprint(base), policy.fingerprint(reordered))

    def test_derived_outcomes_never_reach_the_digest(self):
        base = base_snapshot()
        changed_outcomes = base_snapshot()
        changed_outcomes["outcomes"] = {968: "fail", 985: "dismissed"}
        self.assertEqual(policy.fingerprint(base), policy.fingerprint(changed_outcomes))

    def test_unrelated_pr_fields_never_reach_the_digest(self):
        base = base_snapshot()
        noisy = base_snapshot()
        noisy["prs"][0]["title"] = "a totally different title"
        noisy["reviews"][985][0]["extra"] = "unrelated field"
        self.assertEqual(policy.fingerprint(base), policy.fingerprint(noisy))

class FingerprintInputCoverageTest(unittest.TestCase):
    """Every decision-input class changes the digest: a decision computed
    on an earlier snapshot is never reused after any of them differs."""

    def _assert_changes(self, mutate):
        before = policy.fingerprint(base_snapshot())
        snapshot = base_snapshot()
        mutate(snapshot)
        self.assertNotEqual(policy.fingerprint(snapshot), before)

    def test_last_edited_at_null_to_value_and_value_to_value(self):
        self._assert_changes(lambda s: s["reviews"][968][0].update(last_edited_at="2026-11-12T11:00:00Z"))
        self._assert_changes(lambda s: s["reviews"][968][1].update(last_edited_at="2026-11-13T11:00:00Z"))
        edited = base_snapshot()
        edited["reviews"][985][0]["last_edited_at"] = "2026-11-12T11:00:00Z"
        value_fp = policy.fingerprint(edited)
        self.assertNotEqual(value_fp, policy.fingerprint(base_snapshot()))
        edited["reviews"][985][0]["last_edited_at"] = "2026-11-14T11:00:00Z"
        self.assertNotEqual(policy.fingerprint(edited), value_fp)

    def test_author_fields(self):
        self._assert_changes(lambda s: s["reviews"][968][0].update(author_id=88084960))
        self._assert_changes(lambda s: s["reviews"][968][0].update(author_typename="User"))
        self._assert_changes(lambda s: s["reviews"][968][0].update(author_typename=None))
        self._assert_changes(lambda s: s["reviews"][968][0].update(author_login="other[bot]"))
        self._assert_changes(lambda s: s["reviews"][968][0].update(author_id=None))

    def test_submitted_at_value_and_order(self):
        self._assert_changes(
            lambda s: s["reviews"][968][0].update(submitted_at="2026-11-12T09:30:00Z"))
        # order-relevant: swapping the two records' submitted_at values keeps
        # the multiset but changes which review is newest
        self._assert_changes(
            lambda s: s["reviews"][968][0].update(submitted_at="2026-11-12T10:00:00Z"))
        swapped = base_snapshot()
        swapped["reviews"][968] = snapshot_records()
        swapped["reviews"][968][0]["submitted_at"] = "2026-11-12T10:00:00Z"
        swapped["reviews"][968][1]["submitted_at"] = "2026-11-12T09:00:00Z"
        self.assertNotEqual(policy.fingerprint(swapped), policy.fingerprint(base_snapshot()))

    def test_state_body_commit_oid_and_record_id(self):
        self._assert_changes(lambda s: s["reviews"][968][0].update(state="DISMISSED"))
        self._assert_changes(lambda s: s["reviews"][985][0].update(body="LGTN"))
        self._assert_changes(lambda s: s["reviews"][985][0].update(body=123))
        self._assert_changes(lambda s: s["reviews"][985][0].update(commit_oid="f" * 40))
        self._assert_changes(lambda s: s["reviews"][985][0].update(commit_oid=None))
        self._assert_changes(lambda s: s["reviews"][985][0].update(id=4))

    def test_the_snapshot_sha_key_is_not_an_independent_input(self):
        # the head is bound by each member's head.sha; the top-level key is
        # redundant with it and must not add instability to the digest
        relabeled = base_snapshot()
        relabeled["sha"] = "0" * 40
        self.assertEqual(policy.fingerprint(relabeled), policy.fingerprint(base_snapshot()))

    def test_the_members_head_sha_binds_the_digest(self):
        self._assert_changes(lambda s: s["prs"][0].update(head={"sha": "f" * 40}))
        retargeted = base_snapshot()
        retargeted["prs"][1]["head"]["sha"] = "e" * 40
        self.assertNotEqual(policy.fingerprint(retargeted), policy.fingerprint(base_snapshot()))

    def test_pr_membership_base_and_state(self):
        self._assert_changes(
            lambda s: s["prs"].append(testlib.build_pr_record(number=100, sha=s["sha"])))
        self._assert_changes(lambda s: s["prs"].pop())
        self._assert_changes(lambda s: s["prs"][0]["base"].update(ref="develop"))
        self._assert_changes(lambda s: s["prs"][0].update(state="closed"))
        self._assert_changes(lambda s: s["prs"][0].update(head={"sha": "f" * 40}))

    def test_error_flags_with_their_locations(self):
        self._assert_changes(lambda s: s["api_error"].append("pulls"))
        self._assert_changes(lambda s: s["invalid_input"].append("pr-985"))
        self._assert_changes(lambda s: s["invalid_input"].append("pr-record:number"))
        self._assert_changes(lambda s: s["api_error"].append("pr-968/reviews"))
        flagged = base_snapshot()
        flagged["api_error"] = ["pulls"]
        one_flag = policy.fingerprint(flagged)
        self.assertNotEqual(one_flag, policy.fingerprint(base_snapshot()))
        flagged["api_error"] = ["pulls", "pr-968/reviews"]
        self.assertNotEqual(policy.fingerprint(flagged), one_flag)

    def test_new_and_removed_reviews(self):
        self._assert_changes(
            lambda s: s["reviews"][985].append(
                testlib.build_review_record(id=5, commit_oid=s["sha"], body="late review")))
        self._assert_changes(lambda s: s["reviews"][985].pop())
        self._assert_changes(lambda s: s["reviews"].update({100: []}))

    def test_malformed_prs_shape_changes_the_digest(self):
        self._assert_changes(lambda s: s.update(prs=None))
        self._assert_changes(lambda s: s.update(prs="not-a-list"))
        # two distinct malformed shapes must not collapse to one digest
        none_prs = base_snapshot()
        none_prs["prs"] = None
        str_prs = base_snapshot()
        str_prs["prs"] = "not-a-list"
        self.assertNotEqual(policy.fingerprint(none_prs), policy.fingerprint(str_prs))
        # _jsonable output is always JSON-serializable
        policy.fingerprint({"prs": None, "reviews": {}, "api_error": [], "invalid_input": []})


if __name__ == "__main__":
    unittest.main()
