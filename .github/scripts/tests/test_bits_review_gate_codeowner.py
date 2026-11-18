# Copyright 2026, Datadog, Inc.
"""Tests for the sensitive-path code-owner review gate.

Hermetic through the shared fake transport: sensitive-pattern loading
from CODEOWNERS (default rule excluded, comments and blanks ignored),
path matching (exact, directory-prefix and fnmatch), latest-review
selection with the id tie-breaker, the owner-approval contract (team
member, not the PR author, latest review APPROVED), the per-SHA decision
(no PR, no sensitive path, approval present, approval missing,
self-approval rejected, conjunction) and fail-closed behavior for every
failed read and malformed record. Status publishing carries the exact
context and fails closed on unreadable CODEOWNERS and failed writes.
"""

import json
import os
import sys
import tempfile
import unittest
import unittest.mock

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import bits_review_gate as gate  # noqa: E402
import codeowner_review_gate as cogate  # noqa: E402

import bits_review_gate_testlib as testlib  # noqa: E402
from test_bits_review_gate_api import FakeResponse  # noqa: E402,F401

REPO = "DataDog/java-profiler"
API = "https://api.example.test"
GRAPHQL = "https://api.example.test/graphql"
GITHUB_TOKEN = "gh-read-token"
STATUS_TOKEN = "status-write-token"
SHA = "1" * 40
PULLS_URL = "%s/repos/%s/pulls?state=open&base=main&per_page=100" % (API, REPO)
STATUSES_URL = "%s/repos/%s/commits/%s/statuses?per_page=100" % (API, REPO, SHA)
MEMBERS_URL = "%s/orgs/DataDog/teams/profiling-java/members?per_page=100" % API
TEAM_LOGINS = frozenset({"owner-a", "owner-b"})


def make_client(transport):
    return cogate.CodeownerClient(REPO, transport=transport, env={
        "GITHUB_API_URL": API, "GITHUB_GRAPHQL_URL": GRAPHQL,
        "GITHUB_TOKEN": GITHUB_TOKEN})


COMPARE_URL = "%s/repos/%s/compare/main...%s" % (API, REPO, SHA)
GET_PR_URL = "%s/repos/%s/pulls/101" % (API, REPO)


def compare_page(*names):
    return {"files": files_page(*names)}


def files_page(*names):
    return [{"filename": name, "status": "modified"} for name in names]


def pr(number, head_sha=None, fork=False, **overrides):
    record = testlib.build_pr_record(number, sha=head_sha or SHA)
    record["head"] = {"sha": head_sha or SHA,
                      "repo": {"full_name": "other/fork" if fork else REPO}}
    record["user"] = {"login": "pr-author"}
    record.update(overrides)
    return record


def review(login, state, submitted_at, review_id=1, commit_oid=SHA):
    """A raw GraphQL-shaped review node, exactly what the client returns;
    bound to the evaluated head unless a test overrides the commit."""
    return testlib.build_review_node(
        databaseId=review_id, state=state, submittedAt=submitted_at,
        commit={"oid": commit_oid},
        author={"__typename": "User", "login": login, "databaseId": 7})


def reviews_page(nodes, has_next=False, cursor="cursor-1"):
    return {"data": {"repository": {"pullRequest": {"reviews": {
        "nodes": nodes,
        "pageInfo": {"hasNextPage": has_next, "endCursor": cursor}}}}}}


class SensitivePatternsTest(unittest.TestCase):
    def test_repo_codeowners_marks_gate_paths_and_keeps_default_out(self):
        path = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                            "..", "..", "..", ".github", "CODEOWNERS")
        patterns = cogate.load_sensitive_patterns(path)
        self.assertIn("/.github/workflows/bits-review-gate.yml", patterns)
        self.assertNotIn("*", patterns)

    def test_comments_blanks_and_default_rule_are_skipped(self):
        with tempfile.NamedTemporaryFile("w", suffix="CODEOWNERS",
                                         delete=False) as handle:
            handle.write("# header\n\n"
                         "* @DataDog/profiling-java\n"
                         "/owned/path @DataDog/profiling-java\n"
                         "  \n"
                         "/other/path @DataDog/profiling-java\n")
            name = handle.name
        try:
            self.assertEqual(cogate.load_sensitive_patterns(name),
                             ["/owned/path", "/other/path"])
        finally:
            os.unlink(name)

    def test_entry_naming_another_team_is_rejected(self):
        with tempfile.NamedTemporaryFile("w", suffix="CODEOWNERS",
                                         delete=False) as handle:
            handle.write("/owned/path @DataDog/profiling-java\n"
                         "/other/path @DataDog/other-team\n")
            name = handle.name
        try:
            with self.assertRaises(gate.ApiError):
                cogate.load_sensitive_patterns(name)
        finally:
            os.unlink(name)

    def test_entry_count_at_the_cap_is_accepted_and_over_it_rejected(self):
        with tempfile.NamedTemporaryFile("w", suffix="CODEOWNERS",
                                         delete=False) as handle:
            for index in range(cogate.CODEOWNERS_MAX_ENTRIES - 1):
                handle.write("/p/%d @DataDog/profiling-java\n" % index)
            name = handle.name
        try:
            self.assertEqual(
                len(cogate.load_sensitive_patterns(name)),
                cogate.CODEOWNERS_MAX_ENTRIES - 1)
        finally:
            os.unlink(name)
        with tempfile.NamedTemporaryFile("w", suffix="CODEOWNERS",
                                         delete=False) as handle:
            for index in range(cogate.CODEOWNERS_MAX_ENTRIES):
                handle.write("/p/%d @DataDog/profiling-java\n" % index)
            name = handle.name
        try:
            self.assertEqual(
                len(cogate.load_sensitive_patterns(name)),
                cogate.CODEOWNERS_MAX_ENTRIES)
        finally:
            os.unlink(name)
        with tempfile.NamedTemporaryFile("w", suffix="CODEOWNERS",
                                         delete=False) as handle:
            for index in range(cogate.CODEOWNERS_MAX_ENTRIES + 1):
                handle.write("/p/%d @DataDog/profiling-java\n" % index)
            name = handle.name
        try:
            with self.assertRaises(gate.ApiError):
                cogate.load_sensitive_patterns(name)
        finally:
            os.unlink(name)

    def test_unreadable_file_is_fatal(self):
        with self.assertRaises(gate.ApiError):
            cogate.load_sensitive_patterns(
                os.path.join(tempfile.gettempdir(), "no-such-codeowners-file"))


class SensitiveMatchTest(unittest.TestCase):
    PATTERNS = [".github/workflows/bits-review-gate.yml",
                ".github/scripts/tests/fixtures/bits_review_gate/"]

    def test_exact_path_matches_and_sibling_does_not(self):
        self.assertTrue(cogate.is_sensitive(
            ".github/workflows/bits-review-gate.yml", self.PATTERNS))
        self.assertFalse(cogate.is_sensitive(
            ".github/workflows/ci.yml", self.PATTERNS))

    def test_directory_pattern_matches_contents_not_siblings(self):
        self.assertTrue(cogate.is_sensitive(
            ".github/scripts/tests/fixtures/bits_review_gate/x.json", self.PATTERNS))
        self.assertFalse(cogate.is_sensitive(
            ".github/scripts/tests/fixtures/other/x.json", self.PATTERNS))

    def test_wildcard_pattern_uses_fnmatch(self):
        self.assertTrue(cogate.is_sensitive("docs/x/y.md", ["docs/*/y.md"]))
        self.assertFalse(cogate.is_sensitive("docs/x/z.md", ["docs/*/y.md"]))

    def test_wildcard_directory_pattern_matches_descendants(self):
        # GitHub applies /src/*/secure to src/module/secure/publish.py; a
        # match against the complete filename only would under-block.
        self.assertTrue(cogate.is_sensitive(
            "src/module/secure/publish.py", ["src/*/secure"]))
        self.assertTrue(cogate.is_sensitive(
            "src/module/secure/publish.py", ["/src/*/secure"]))
        self.assertFalse(cogate.is_sensitive(
            "src/module/insecure/publish.py", ["/src/*/secure"]))

    def test_wildcard_directory_pattern_with_trailing_slash_matches_descendants(self):
        self.assertTrue(cogate.is_sensitive(
            "src/a/build/x.py", ["/src/*/build/"]))
        self.assertFalse(cogate.is_sensitive(
            "src/a/dist/x.py", ["/src/*/build/"]))

    def test_double_star_wildcard_covers_root_level_files(self):
        # GitHub applies /**/x.gradle.kts to a root-level x.gradle.kts;
        # fnmatch alone would demand a literal / in the path and let the
        # root-level file escape the gate.
        self.assertTrue(cogate.is_sensitive(
            "build.gradle.kts", ["/**/*.gradle.kts"]))
        self.assertTrue(cogate.is_sensitive(
            "ddprof-lib/build.gradle.kts", ["/**/*.gradle.kts"]))

    def test_malformed_member_record_fails_the_roster_read(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, ["not-a-member"]),
        ])
        with self.assertRaises(gate.ApiError):
            make_client(transport).team_logins("DataDog", "profiling-java")
        transport = testlib.FakeTransport([
            FakeResponse(200, [{"login": None}]),
        ])
        with self.assertRaises(gate.ApiError):
            make_client(transport).team_logins("DataDog", "profiling-java")

    def test_leading_slash_is_dropped_before_matching(self):
        self.assertTrue(cogate.is_sensitive(
            ".github/scripts/deploy.sh", ["/.github/scripts/deploy.sh"]))
        self.assertFalse(cogate.is_sensitive(
            "docs/deploy.sh", ["/.github/scripts/deploy.sh"]))

    def test_unanchored_pattern_is_rejected(self):
        with tempfile.NamedTemporaryFile("w", suffix="CODEOWNERS",
                                         delete=False) as handle:
            handle.write("docs/*/y.md @DataDog/profiling-java\n")
            name = handle.name
        try:
            with self.assertRaises(gate.ApiError):
                cogate.load_sensitive_patterns(name)
        finally:
            os.unlink(name)


class LatestReviewTest(unittest.TestCase):
    def test_latest_by_submission_time_wins(self):
        records = [gate.normalize_review(n) for n in [
            review("owner-a", "APPROVED", "2026-01-01T00:00:00Z", 1),
            review("owner-a", "CHANGES_REQUESTED", "2026-01-02T00:00:00Z", 2)]]
        self.assertEqual(cogate.latest_review_by_login(records)["owner-a"]["state"],
                         "CHANGES_REQUESTED")

    def test_equal_submission_time_breaks_the_tie_by_id(self):
        records = [gate.normalize_review(n) for n in [
            review("owner-a", "APPROVED", "2026-01-01T00:00:00Z", 1),
            review("owner-a", "COMMENTED", "2026-01-01T00:00:00Z", 2)]]
        self.assertEqual(cogate.latest_review_by_login(records)["owner-a"]["state"],
                         "COMMENTED")

    def test_records_without_login_are_ignored(self):
        records = [{"author_login": None, "state": "APPROVED",
                    "submitted_at": "2026-01-01T00:00:00Z", "id": 1}]
        self.assertEqual(cogate.latest_review_by_login(records), {})


class OwnerApprovalTest(unittest.TestCase):
    def test_team_member_approval_counts(self):
        records = [gate.normalize_review(review("owner-a", "APPROVED",
                                            "2026-01-01T00:00:00Z"))]
        self.assertTrue(cogate.owner_approval(records, "pr-author", TEAM_LOGINS, SHA))

    def test_self_approval_never_counts(self):
        records = [gate.normalize_review(review("pr-author", "APPROVED",
                                            "2026-01-01T00:00:00Z"))]
        self.assertFalse(cogate.owner_approval(records, "pr-author", TEAM_LOGINS, SHA))

    def test_author_in_the_roster_still_cannot_approve_own_pr(self):
        # The author being a roster member must not defeat the exclusion:
        # only the head-bound approval of another member counts.
        records = [gate.normalize_review(review("owner-a", "APPROVED",
                                            "2026-01-01T00:00:00Z"))]
        self.assertFalse(cogate.owner_approval(
            records, "owner-a", TEAM_LOGINS, SHA))
        records.append(gate.normalize_review(
            review("owner-b", "APPROVED", "2026-01-02T00:00:00Z", 2)))
        self.assertTrue(cogate.owner_approval(
            records, "owner-a", TEAM_LOGINS, SHA))

    def test_non_member_approval_does_not_count(self):
        records = [gate.normalize_review(review("outsider", "APPROVED",
                                            "2026-01-01T00:00:00Z"))]
        self.assertFalse(cogate.owner_approval(records, "pr-author", TEAM_LOGINS, SHA))

    def test_superseded_approval_does_not_count(self):
        records = [gate.normalize_review(n) for n in [
            review("owner-a", "APPROVED", "2026-01-01T00:00:00Z", 1),
            review("owner-a", "CHANGES_REQUESTED",
                   "2026-01-02T00:00:00Z", 2)]]
        self.assertFalse(cogate.owner_approval(records, "pr-author", TEAM_LOGINS, SHA))

    def test_approval_on_another_commit_does_not_count(self):
        records = [gate.normalize_review(review(
            "owner-a", "APPROVED", "2026-01-01T00:00:00Z", commit_oid="2" * 40))]
        self.assertFalse(cogate.owner_approval(records, "pr-author", TEAM_LOGINS, SHA))


class EvaluateShaTest(unittest.TestCase):
    def evaluate(self, transport):
        client = make_client(transport)
        client._team_logins = TEAM_LOGINS
        return cogate.evaluate_sha(SHA, client,
                                   [".github/scripts/bits_review_gate.py"])

    def test_no_open_pr_at_sha_yields_empty(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, []),
        ])
        self.assertEqual(self.evaluate(transport)[0], "empty")

    def test_pr_without_sensitive_paths_passes(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page("doc/README.md")),
            FakeResponse(200, pr(101)),
        ])
        self.assertEqual(self.evaluate(transport)[1], "success")

    def test_fork_head_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101, fork=True)]),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("fork pull request", description)

    def test_moved_head_after_reads_writes_nothing(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page("doc/README.md")),
            FakeResponse(200, pr(101, head_sha="3" * 40)),
        ])
        self.assertEqual(self.evaluate(transport)[0], "empty")

    def test_closed_pr_after_reads_writes_nothing(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page("doc/README.md")),
            FakeResponse(200, testlib.build_pr_record(
                101, sha=SHA, state="closed")),
        ])
        self.assertEqual(self.evaluate(transport)[0], "empty")

    def test_sensitive_path_without_owner_review_fails_with_target_url(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                "doc/README.md", ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page([])),
            FakeResponse(200, pr(101)),
        ])
        kind, state, description, target_url = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("approval from @DataDog/profiling-java required", description)
        self.assertEqual(target_url, "https://github.com/" + REPO + "/pull/101")

    def test_sensitive_path_with_owner_review_passes(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page(
                [review("owner-a", "APPROVED", "2026-01-01T00:00:00Z")])),
            FakeResponse(200, pr(101)),
        ])
        self.assertEqual(self.evaluate(transport)[1], "success")

    def test_self_approval_on_sensitive_path_fails(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page(
                [review("pr-author", "APPROVED", "2026-01-01T00:00:00Z")])),
            FakeResponse(200, pr(101)),
        ])
        self.assertEqual(self.evaluate(transport)[1], "failure")

    def test_non_member_approval_on_sensitive_path_fails(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page(
                [review("outsider", "APPROVED", "2026-01-01T00:00:00Z")])),
            FakeResponse(200, pr(101)),
        ])
        self.assertEqual(self.evaluate(transport)[1], "failure")

    def test_renamed_sensitive_file_is_caught_by_previous_name(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, {"files": [
                {"filename": "renamed-away.py", "status": "renamed",
                 "previous_filename": ".github/scripts/bits_review_gate.py"}]}),
            FakeResponse(200, reviews_page([])),
            FakeResponse(200, pr(101)),
        ])
        self.assertEqual(self.evaluate(transport)[1], "failure")

    def test_failed_files_read_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(500, []),
            FakeResponse(500, []),
            FakeResponse(500, []),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("files read failed", description)

    def test_compare_at_the_file_cap_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, {"files": files_page(*(
                "f/%d.py" % index for index in range(300)))}),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("split the pull request", description)

    def test_file_cap_is_labeled_as_a_size_problem_not_a_read_failure(self):
        # The author must be able to tell a deliberate size cap from a
        # transient read failure: only the cap message says what to do.
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, {"files": files_page(*(
                "f/%d.py" % index for index in range(300)))}),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertIn("at or above the 300 cap", description)
        self.assertNotIn("read failed", description)

    def test_failed_reviews_read_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            gate.RateLimitError("rate limit"),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("reviews read failed", description)

    def test_malformed_pr_record_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, ["not-a-record"]),
        ])
        self.assertEqual(self.evaluate(transport)[1], "failure")

    def test_pr_with_malformed_head_sha_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [testlib.build_pr_record(101, head={"sha": None})]),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("malformed PR record", description)

    def test_pr_with_malformed_author_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [testlib.build_pr_record(
                101, sha=SHA, user={"id": 5})]),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("malformed PR record", description)

    def test_pr_with_malformed_base_ref_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [testlib.build_pr_record(
                101, sha=SHA, base={"ref": None})]),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("malformed PR record", description)

    def test_pr_headed_elsewhere_is_skipped(self):
        # The only open PR at the listing carries a different head SHA: it
        # is not this evaluation's subject and the SHA yields empty.
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101, head_sha="3" * 40)]),
        ])
        self.assertEqual(self.evaluate(transport)[0], "empty")

    def test_roster_member_author_cannot_self_approve_at_sha_level(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101, **{"user": {"login": "owner-a"}})]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page(
                [review("owner-a", "APPROVED", "2026-01-01T00:00:00Z")])),
            FakeResponse(200, pr(101)),
        ])
        self.assertEqual(self.evaluate(transport)[1], "failure")

    def test_failed_team_roster_read_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page([])),
            FakeResponse(500, []),
            FakeResponse(500, []),
            FakeResponse(500, []),
        ])
        client = make_client(transport)
        kind, state, description, _ = cogate.evaluate_sha(
            SHA, client, [".github/scripts/bits_review_gate.py"])
        self.assertEqual(state, "failure")
        self.assertIn("team roster read failed", description)

    def test_malformed_file_entry_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, {"files": [{"status": "modified"}]}),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("files read failed", description)

    def test_identical_timestamp_and_id_keeps_the_first_record(self):
        records = [gate.normalize_review(n) for n in [
            review("owner-a", "APPROVED", "2026-01-01T00:00:00Z", 7),
            review("owner-a", "COMMENTED", "2026-01-01T00:00:00Z", 7)]]
        self.assertEqual(cogate.latest_review_by_login(records)["owner-a"]["state"],
                         "APPROVED")

    def test_failing_member_in_conjunction_fails_the_sha(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101), pr(102)]),
            FakeResponse(200, compare_page("doc/README.md")),
            FakeResponse(200, pr(101)),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page([])),
            FakeResponse(200, pr(102)),
        ])
        self.assertEqual(self.evaluate(transport)[1], "failure")

    def test_failed_pulls_read_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(500, []),
            FakeResponse(500, []),
            FakeResponse(500, []),
        ])
        self.assertEqual(self.evaluate(transport)[1], "failure")

    def test_malformed_revalidation_record_fails_closed(self):
        # The approval stands, but the final PR read returns a record with
        # no usable head: publishing nothing would leave a recorded success
        # in place, so the outcome is a failure status instead.
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page(
                [review("owner-a", "APPROVED", "2026-01-01T00:00:00Z")])),
            FakeResponse(200, {"state": "open", "head": None}),
        ])
        kind, state, description, _ = self.evaluate(transport)
        self.assertEqual(state, "failure")
        self.assertIn("PR 101 revalidation failed", description)


class PublishTest(unittest.TestCase):
    def publish(self, transport, codeowners=None):
        client = make_client(transport)
        client._team_logins = TEAM_LOGINS
        if codeowners is None:
            with unittest.mock.patch.object(
                    cogate, "load_sensitive_patterns",
                    return_value=[".github/scripts/bits_review_gate.py"]):
                return cogate.publish(SHA, client, STATUS_TOKEN)
        with tempfile.NamedTemporaryFile("w", suffix="CODEOWNERS",
                                         delete=False) as handle:
            handle.write(codeowners)
            name = handle.name
        try:
            with unittest.mock.patch.object(cogate, "CODEOWNERS_PATH", name):
                return cogate.publish(SHA, client, STATUS_TOKEN)
        finally:
            os.unlink(name)

    def response_for_flow(self, sensitive, approval):
        """Responses for one PR flow: pulls, compare, reviews (sensitive
        only), the revalidation read, the statuses read for suppression,
        and the 200 that the status POST consumes. The roster comes from
        the seeded client cache, not from a queued response."""
        responses = [FakeResponse(200, [pr(101)]),
                     FakeResponse(
                         200, compare_page(".github/scripts/bits_review_gate.py"
                                           if sensitive else "doc/README.md"))]
        if sensitive:
            nodes = [review("owner-a", "APPROVED", "2026-01-01T00:00:00Z")] \
                if approval else []
            responses.append(FakeResponse(200, reviews_page(nodes)))
        responses.append(FakeResponse(200, pr(101)))
        responses.append(FakeResponse(200, []))
        responses.append(FakeResponse(200, []))
        return responses

    def recorded_status(self, state):
        return {"id": 1, "context": cogate.STATUS_CONTEXT, "state": state,
                "description": "sensitive-path owner review satisfied",
                "target_url": None,
                "creator": {"login": gate.STATUS_CREATOR}}

    def test_pass_publishes_success_with_context(self):
        transport = testlib.FakeTransport(self.response_for_flow(False, False))
        code = self.publish(transport)
        self.assertEqual(code, 0)
        request = transport.calls[-1]
        self.assertTrue(request.full_url.endswith("/statuses/" + SHA))
        payload = json.loads(request.data)
        self.assertEqual(payload["context"], "codeowner-review/head")
        self.assertEqual(payload["state"], "success")

    def test_membership_read_uses_the_status_token(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page([])),
            FakeResponse(200, [{"login": "owner-a"}]),
            FakeResponse(200, pr(101)),
            FakeResponse(200, []),
            FakeResponse(200, []),
        ])
        client = make_client(transport)
        self.assertEqual(cogate.publish(SHA, client, STATUS_TOKEN), 1)
        member_calls = [call for call in transport.calls
                        if "/teams/profiling-java/members" in call.full_url]
        self.assertEqual(len(member_calls), 1)
        self.assertEqual(member_calls[0].headers.get("Authorization"),
                         "Bearer " + STATUS_TOKEN)

    def test_identical_status_is_not_republished(self):
        # Drop the plain statuses-read and the POST slot; the recorded
        # status becomes the statuses-read response.
        transport = testlib.FakeTransport(self.response_for_flow(True, True)[:-2]
                                          + [FakeResponse(200, [
                                              self.recorded_status("success")])])
        client = make_client(transport)
        client._team_logins = TEAM_LOGINS
        self.assertEqual(cogate.publish(SHA, client, STATUS_TOKEN), 0)
        self.assertFalse(
            any(call.full_url.endswith("/statuses/" + SHA)
                for call in transport.calls))

    def test_changed_status_is_republished(self):
        transport = testlib.FakeTransport(self.response_for_flow(True, False)[:-2]
                                          + [FakeResponse(200, [
                                              self.recorded_status("success")])])
        client = make_client(transport)
        client._team_logins = TEAM_LOGINS
        self.assertEqual(cogate.publish(SHA, client, STATUS_TOKEN), 1)
        self.assertTrue(
            any("/statuses/" in call.full_url for call in transport.calls))

    def test_no_open_pr_writes_nothing(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, []),
        ])
        client = make_client(transport)
        self.assertEqual(cogate.publish(SHA, client, STATUS_TOKEN), 0)
        self.assertFalse(
            any(call.full_url.endswith("/statuses/" + SHA)
                for call in transport.calls))

    def test_missing_owner_review_publishes_failure_and_exits_one(self):
        transport = testlib.FakeTransport(self.response_for_flow(True, False))
        self.assertEqual(self.publish(transport), 1)
        payload = json.loads(transport.calls[-1].data)
        self.assertEqual(payload["state"], "failure")

    def test_owner_review_publishes_success_and_exits_zero(self):
        transport = testlib.FakeTransport(self.response_for_flow(True, True))
        self.assertEqual(self.publish(transport), 0)

    def test_failed_write_exits_one(self):
        # The flow's final 200 is replaced by three 5xx: the status POST
        # exhausts its attempts and the write fails.
        transport = testlib.FakeTransport(
            self.response_for_flow(False, False)[:-1]
            + [FakeResponse(500, []) for _ in range(3)])
        self.assertEqual(self.publish(transport), 1)

    def test_oversized_description_is_truncated(self):
        with unittest.mock.patch.object(
                cogate, "load_sensitive_patterns",
                return_value=["x" * 200]):
            transport = testlib.FakeTransport([
                FakeResponse(200, [pr(101)]),
                FakeResponse(200, compare_page("x" * 200)),
                FakeResponse(200, reviews_page([])),
                FakeResponse(200, pr(101)),
                FakeResponse(200, []),
                FakeResponse(200, []),
            ])
            self.assertEqual(self.publish(transport), 1)
        payload = json.loads(transport.calls[-1].data)
        self.assertLessEqual(len(payload["description"]), 140)

    def test_malformed_revalidation_publishes_failure(self):
        # The suppression skip must not fire on a malformed revalidation
        # record: the failure status replaces any recorded success.
        transport = testlib.FakeTransport([
            FakeResponse(200, [pr(101)]),
            FakeResponse(200, compare_page(
                ".github/scripts/bits_review_gate.py")),
            FakeResponse(200, reviews_page(
                [review("owner-a", "APPROVED", "2026-01-01T00:00:00Z")])),
            FakeResponse(200, {"state": "open", "head": None}),
            FakeResponse(200, [self.recorded_status("success")]),
            FakeResponse(200, []),
        ])
        client = make_client(transport)
        client._team_logins = TEAM_LOGINS
        self.assertEqual(cogate.publish(SHA, client, STATUS_TOKEN), 1)
        payload = json.loads(transport.calls[-1].data)
        self.assertEqual(payload["state"], "failure")
        self.assertIn("revalidation failed", payload["description"])

    def test_unreadable_codeowners_fails_closed(self):
        # A missing CODEOWNERS file is fatal before any evaluation: point
        # the module constant at a path that cannot exist.
        with unittest.mock.patch.object(
                cogate, "CODEOWNERS_PATH",
                os.path.join(tempfile.gettempdir(), "no-such-codeowners")):
            self.assertEqual(cogate.publish(
                SHA, make_client(testlib.FakeTransport([])), STATUS_TOKEN), 1)

    def test_sha_argument_must_be_forty_hex(self):
        with self.assertRaises(SystemExit):
            cogate.main(["publish", "--sha", "not-a-sha"])


class SelectedStatusTest(unittest.TestCase):
    def status(self, status_id, creator=gate.STATUS_CREATOR,
               context=cogate.STATUS_CONTEXT, state="success",
               description="d", target_url=None):
        return {"id": status_id, "context": context, "state": state,
                "description": description, "target_url": target_url,
                "creator": {"login": creator}}

    def test_only_own_creator_and_context_are_candidates(self):
        statuses = [
            self.status(1, creator="someone-else"),
            self.status(2, context="other-context"),
            self.status(3),
        ]
        self.assertEqual(cogate._selected_status(statuses)["id"], 3)

    def test_highest_id_wins_regardless_of_order(self):
        statuses = [self.status(9), self.status(12), self.status(4)]
        self.assertEqual(cogate._selected_status(statuses)["id"], 12)

    def test_equal_id_keeps_the_first_seen(self):
        # A duplicated id must not let the later record replace the first
        # candidate: >= here would make the choice order-dependent.
        statuses = [self.status(9, state="failure"), self.status(9)]
        self.assertEqual(cogate._selected_status(statuses)["state"], "failure")

    def test_no_candidate_returns_none(self):
        self.assertIsNone(cogate._selected_status(
            [self.status(1, creator="someone-else")]))

    def test_every_field_must_match_for_suppression(self):
        recorded = self.status(
            1, description="sensitive-path owner review satisfied")
        payload = {"state": "success", "context": cogate.STATUS_CONTEXT,
                   "description": "sensitive-path owner review satisfied"}
        self.assertTrue(cogate._matches_status(recorded, payload))
        # Same state but a different description is a changed status: the
        # description comparison is what keeps stale text from suppressing
        # a fresh write.
        self.assertFalse(cogate._matches_status(
            self.status(1, description="other text"), payload))
        self.assertFalse(cogate._matches_status(
            self.status(1, state="failure"), payload))


class TeamLoginsTest(unittest.TestCase):
    def test_page_cap_fails_the_read(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [{"login": "owner-a"}],
                         link="<%s&page=2>; rel=\"next\"" % MEMBERS_URL)
        ] * (gate.MAX_FETCH_PAGES + 1))
        client = make_client(transport)
        with self.assertRaises(gate.ApiError):
            client.team_logins("DataDog", "profiling-java")

if __name__ == "__main__":
    unittest.main()
