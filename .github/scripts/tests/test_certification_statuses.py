# Copyright 2026, Datadog, Inc.
"""Offline GitHub API fixtures exercise the real certification waiter and its CLI.

Fixtures reproduce REST status ordering, pagination and rotating publisher identities.
They cannot prove the permissions of the live Actions GITHUB_TOKEN.
"""

from collections import deque
from contextlib import ExitStack
import http.client
import io
import json
import os
from pathlib import Path
import socket
import sys
import tempfile
import unittest
from unittest.mock import patch
import urllib.error
import urllib.parse

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import wait_for_integration as gate  # noqa: E402


REPO = "DataDog/java-profiler"
SHA = "7a8f24862288f68679caf69ff5a53bfe34ce74b6"
CONTEXTS = (
    "dd-gitlab/prepare-patched-agent",
    "dd-gitlab/validate-dd-trace-quarantine",
    "dd-gitlab/post-pr-comment",
)
BOTS = {
    "gitsync-ddbuild-stable1": 65570472,
    "gitsync-ddbuild-stable9": 107991031,
    "dd-ghss-ciux-19": 266815189,
    "dd-ghss-ciexecution-15": 226300137,
}


def status(context, state="success", slug="gitsync-ddbuild-stable1", **changes):
    record = {
        "context": context,
        "state": state,
        "url": f"https://api.github.com/repos/{REPO}/statuses/{SHA}",
        "creator": {"login": slug + "[bot]", "id": BOTS[slug], "type": "Bot"},
    }
    record.update(changes)
    return record


def green():
    return [status(context) for context in CONTEXTS]


def page_path(page=1):
    return f"/repos/{REPO}/commits/{SHA}/statuses?per_page=100&page={page}"


class CertificationStatusTest(unittest.TestCase):
    def setUp(self):
        self.now = 1000
        self.sleeps = []
        self.requests = []
        self.responses = {}
        self.output = io.StringIO()
        self.errors = io.StringIO()
        stack = ExitStack()
        self.addCleanup(stack.close)
        stack.enter_context(patch.object(gate.OPENER, "open", side_effect=self.open))
        stack.enter_context(patch.object(gate.time, "monotonic", side_effect=lambda: self.now))
        stack.enter_context(patch.object(gate.time, "sleep", side_effect=self.sleep))
        stack.enter_context(patch.object(sys, "stdout", self.output))
        stack.enter_context(patch.object(sys, "stderr", self.errors))
        stack.enter_context(patch.dict(os.environ, {}, clear=True))
        stack.enter_context(patch.object(socket, "socket", side_effect=AssertionError("Network forbidden")))
        self.api = gate.GitHub(REPO, "test-token", self.now + 600)

    def sleep(self, seconds):
        self.sleeps.append(seconds)
        self.now += seconds

    def queue(self, path, *responses):
        self.responses[path] = deque(responses)

    def open(self, request, *, timeout):
        self.assertEqual(request.get_method(), "GET")
        self.assertEqual(request.get_header("Authorization"), "Bearer test-token")
        self.assertEqual(request.get_header("X-github-api-version"), "2022-11-28")
        self.assertEqual(request.get_header("User-agent"), "java-profiler-certification")
        self.assertGreater(timeout, 0)
        self.assertLessEqual(timeout, min(30, self.api.deadline - self.now))
        url = urllib.parse.urlsplit(request.full_url)
        self.assertEqual((url.scheme, url.netloc), ("https", "api.github.com"))
        path = url.path + ("?" + url.query if url.query else "")
        self.requests.append(path)
        if path in self.responses:
            self.assertTrue(self.responses[path], "Unexpected extra read of " + path)
            response = self.responses[path].popleft()
        elif path.startswith("/apps/"):
            slug = path.removeprefix("/apps/")
            self.assertIn(slug, BOTS)
            response = {"slug": slug, "owner": {"id": 365230, "type": "Organization"}}
        elif path.startswith("/users/"):
            login = urllib.parse.unquote(path.removeprefix("/users/"))
            slug = login.removesuffix("[bot]")
            response = {"login": login, "id": BOTS[slug], "type": "Bot"}
        else:
            self.fail("Unexpected GitHub API path: " + path)
        if callable(response):
            response = response()
        if isinstance(response, Exception):
            raise response
        return io.BytesIO(response if isinstance(response, bytes) else json.dumps(response).encode())

    def wait(self):
        gate.wait_for_integration(self.api, SHA)

    def assert_rejected(self, records, message):
        self.queue(page_path(), records)
        with self.assertRaisesRegex(gate.GateError, message):
            self.wait()
        self.assertEqual(self.sleeps, [])

    def test_all_required_verdicts_succeed_and_summary_appends(self):
        with tempfile.TemporaryDirectory() as directory:
            summary = Path(directory) / "summary"
            summary.write_text("previous summary\n")
            os.environ["GITHUB_STEP_SUMMARY"] = str(summary)
            self.queue(page_path(), green())
            self.wait()
            text = summary.read_text()
        self.assertTrue(text.startswith("previous summary\n"))
        self.assertIn(SHA, text)
        for context in CONTEXTS:
            self.assertIn(context + ": success", text)
        self.assertEqual(self.sleeps, [])
        self.assertEqual(self.requests.count("/apps/gitsync-ddbuild-stable1"), 1)
        self.assertEqual(self.requests.count("/users/gitsync-ddbuild-stable1%5Bbot%5D"), 1)

    def test_each_required_context_is_mandatory_even_with_overall_green(self):
        for missing in CONTEXTS:
            with self.subTest(missing=missing):
                self.api.deadline = self.now + 1
                self.queue(page_path(), [record for record in green() if record["context"] != missing]
                           + [status("dd-gitlab/default-pipeline")])
                with self.assertRaisesRegex(gate.GateError, "Timed out"):
                    self.wait()
                self.assertIn(missing + ": missing", self.output.getvalue())

    def test_missing_then_pending_then_success_refreshes_all_statuses(self):
        pending = green()
        pending[-1]["state"] = "pending"
        self.queue(page_path(), [], pending, green())
        self.wait()
        self.assertEqual(self.sleeps, [180, 180])
        self.assertEqual(self.requests.count(page_path()), 3)
        self.assertEqual(self.requests.count("/apps/gitsync-ddbuild-stable1"), 1)

    def test_failure_and_error_in_each_context_block_without_waiting(self):
        for context in CONTEXTS:
            for state in ("failure", "error"):
                with self.subTest(context=context, state=state):
                    records = green()
                    next(record for record in records if record["context"] == context)["state"] = state
                    self.assert_rejected(records, "verdict failed")
                    self.assertIn(context + ": " + state, self.output.getvalue())

    def test_raw_failed_cells_do_not_override_quarantine_aware_verdict(self):
        self.queue(page_path(), [status("dd-gitlab/integration-test-x64-glibc", "failure")]
                   + green())
        self.wait()
        self.assertEqual(self.sleeps, [])

    def test_newest_failure_beats_older_success(self):
        self.assert_rejected([status(CONTEXTS[-1], "failure")] + green(), "verdict failed")

    def test_newest_pending_beats_older_success_including_context_case(self):
        self.queue(page_path(), [status(CONTEXTS[-1].upper(), "pending")] + green(), green())
        self.wait()
        self.assertEqual(self.sleeps, [180])

    def test_newest_untrusted_update_cannot_fall_back_to_old_success(self):
        untrusted = status(CONTEXTS[0], creator={"login": "someone", "type": "User", "id": 1})
        self.assert_rejected([untrusted] + green(), "untrusted publisher")
        self.assertIn(CONTEXTS[0] + ": unverified", self.output.getvalue())

    def test_rotating_bridge_app_families_are_verified_individually(self):
        for slug in BOTS:
            with self.subTest(slug=slug):
                self.queue(page_path(), [status(context, slug=slug) for context in CONTEXTS])
                self.wait()
                self.assertIn("/apps/" + slug, self.requests)
                self.assertIn("/users/" + slug + "%5Bbot%5D", self.requests)

    def test_invalid_publisher_shapes_and_families_are_rejected(self):
        for creator in (None, [], {}, {"login": 1},
                        {"login": "unrelated[bot]", "id": 1, "type": "Bot"},
                        {"login": "gitsync-ddbuild-stable1[bot]evil", "id": 1, "type": "Bot"},
                        {"login": "gitsync-ddbuild-stable1[bot]", "id": True, "type": "Bot"},
                        {"login": "gitsync-ddbuild-stable1[bot]", "id": 0, "type": "Bot"},
                        {"login": "gitsync-ddbuild-stable1[bot]", "id": 1, "type": "User"}):
            with self.subTest(creator=creator):
                self.assert_rejected([status(CONTEXTS[0], creator=creator)] + green(),
                                     "publisher")

    def test_identity_cache_is_keyed_by_both_login_and_id(self):
        pending = green()
        pending[-1]["state"] = "pending"
        impersonated = green()
        impersonated[0]["creator"]["id"] = 1
        self.queue(page_path(), pending, impersonated)
        with self.assertRaisesRegex(gate.GateError, "not a Datadog bridge app"):
            self.wait()
        self.assertEqual(self.requests.count("/apps/gitsync-ddbuild-stable1"), 2)
        self.assertEqual(self.sleeps, [180])

    def test_app_metadata_must_identify_a_datadog_owned_bridge(self):
        for app in ([], {}, {"slug": "other"},
                    {"slug": "gitsync-ddbuild-stable1", "owner": []},
                    {"slug": "gitsync-ddbuild-stable1", "owner": {"id": 1, "type": "Organization"}},
                    {"slug": "gitsync-ddbuild-stable1", "owner": {"id": 365230, "type": "User"}}):
            with self.subTest(app=app):
                self.api.trusted_bots.clear()
                self.queue("/apps/gitsync-ddbuild-stable1", app)
                self.assert_rejected(green(), "not a Datadog bridge app")

    def test_current_bot_account_must_match_all_identity_fields(self):
        original = {"login": "gitsync-ddbuild-stable1[bot]", "id": 65570472, "type": "Bot"}
        for bot in ([], {}, dict(original, login="other[bot]"),
                    dict(original, id=42), dict(original, type="User")):
            with self.subTest(bot=bot):
                self.api.trusted_bots.clear()
                self.queue("/users/gitsync-ddbuild-stable1%5Bbot%5D", bot)
                self.assert_rejected(green(), "not a Datadog bridge app")

    def test_boolean_account_id_cannot_match_numeric_creator_id(self):
        self.queue("/users/gitsync-ddbuild-stable1%5Bbot%5D",
                   {"login": "gitsync-ddbuild-stable1[bot]", "id": True, "type": "Bot"})
        record = status(CONTEXTS[0], creator={
            "login": "gitsync-ddbuild-stable1[bot]", "id": 1, "type": "Bot"})
        self.assert_rejected([record] + green(), "not a Datadog bridge app")

    def test_status_url_must_bind_exact_sha_repository_and_api(self):
        for url in (None, "https://evil.example/statuses/" + SHA,
                    f"https://api.github.com/repos/other/repo/statuses/{SHA}",
                    f"https://api.github.com/repos/{REPO}/statuses/" + "f" * 40):
            with self.subTest(url=url):
                self.assert_rejected([status(CONTEXTS[0], url=url)] + green(), "candidate SHA")

    def test_invalid_record_or_state_fails_closed(self):
        for records in ([None], [{"context": None}], ["not a status"],
                        [status(CONTEXTS[0], state="skipped")] + green(),
                        [status(CONTEXTS[0], state=None)] + green()):
            with self.subTest(records=records):
                self.assert_rejected(records, "Malformed|Invalid")

    def test_required_context_on_second_page_is_not_missed(self):
        self.queue(page_path(), [status("unrelated")] * 100)
        self.queue(page_path(2), green())
        self.wait()
        self.assertIn(page_path(2), self.requests)

    def test_exactly_full_last_page_requires_empty_following_page(self):
        self.queue(page_path(), green() + [status("unrelated")] * 97)
        self.queue(page_path(2), [])
        self.wait()
        self.assertEqual(self.requests[:2], [page_path(), page_path(2)])

    def test_failed_later_page_discards_partial_green_snapshot(self):
        self.queue(page_path(), green() + [status("unrelated")] * 97,
                   [status(CONTEXTS[0], "failure")] + green())
        self.queue(page_path(2), urllib.error.URLError("offline"))
        with self.assertRaisesRegex(gate.GateError, "verdict failed"):
            self.wait()
        self.assertEqual(self.sleeps, [180])
        self.assertEqual(self.requests.count(page_path()), 2)

    def test_non_array_and_excessive_pagination_fail_closed(self):
        self.queue(page_path(), {})
        with self.assertRaisesRegex(gate.GateError, "not an array"):
            self.wait()
        self.queue(page_path(), [status("unrelated")] * 100)
        self.queue(page_path(2), [status("unrelated")] * 100)
        with patch.object(gate, "MAX_PAGES", 2):
            with self.assertRaisesRegex(gate.GateError, "pagination limit"):
                self.wait()
        self.assertEqual(self.sleeps, [])

    def test_transport_invalid_json_and_incomplete_response_retry(self):
        for error in (urllib.error.URLError("offline"), TimeoutError(),
                      http.client.IncompleteRead(b"{", 10), b"not JSON"):
            with self.subTest(error=error):
                self.queue(page_path(), error, green())
                before = len(self.sleeps)
                self.api.deadline = self.now + 600
                self.wait()
                self.assertEqual(len(self.sleeps), before + 1)

    def test_transient_http_errors_retry_but_auth_and_redirects_do_not(self):
        for code, headers, retry in ((502, {}, True), (429, {}, True),
                                     (403, {"X-RateLimit-Remaining": "0"}, True),
                                     (401, {}, False), (403, {}, False),
                                     (404, {}, False), (302, {}, False)):
            with self.subTest(code=code, headers=headers):
                error = urllib.error.HTTPError("https://api.github.com", code,
                                               "failure", headers, None)
                self.queue(page_path(), error, green())
                self.api.deadline = self.now + 600
                before = len(self.sleeps)
                if retry:
                    self.wait()
                else:
                    with self.assertRaisesRegex(gate.GateError, "GitHub HTTP " + str(code)):
                        self.wait()
                self.assertEqual(len(self.sleeps), before + int(retry))

    def test_transient_identity_read_failure_retries_complete_snapshot(self):
        self.queue(page_path(), green(), green())
        self.queue("/apps/gitsync-ddbuild-stable1", urllib.error.URLError("offline"),
                   {"slug": "gitsync-ddbuild-stable1", "owner": {"id": 365230, "type": "Organization"}})
        self.wait()
        self.assertEqual(self.requests.count(page_path()), 2)
        self.assertEqual(self.sleeps, [180])

    def test_deadline_bounds_sleep_and_reports_missing_or_unavailable(self):
        for response, state in (([], "missing"), (urllib.error.URLError("offline"), "unavailable")):
            with self.subTest(state=state):
                self.api.deadline = self.now + 17
                self.queue(page_path(), response)
                with self.assertRaisesRegex(gate.GateError, "Timed out"):
                    self.wait()
                self.assertEqual(self.sleeps[-1], 17)
                self.assertIn(CONTEXTS[0] + ": " + state, self.output.getvalue())

    def test_api_calls_after_deadline_are_not_started(self):
        self.api.deadline = self.now
        with self.assertRaisesRegex(gate.GateError, "Timed out"):
            self.api.get(page_path())
        self.assertEqual(self.requests, [])

    def test_request_timeout_uses_remaining_budget(self):
        self.api.deadline = self.now + 7
        self.queue(page_path(), green())
        self.api.get(page_path())
        self.assertEqual(gate.OPENER.open.call_args.kwargs["timeout"], 7)

    def test_slow_snapshot_cannot_succeed_after_deadline(self):
        def slow_green():
            self.now = self.api.deadline
            return green()
        self.queue(page_path(), slow_green)
        with self.assertRaisesRegex(gate.GateError, "Timed out"):
            self.wait()
        self.assertEqual(self.sleeps, [])

    def test_final_identity_read_cannot_certify_after_deadline(self):
        def slow_bot():
            self.now = self.api.deadline
            return {"login": "gitsync-ddbuild-stable1[bot]", "id": 65570472, "type": "Bot"}
        self.queue(page_path(), green())
        self.queue("/users/gitsync-ddbuild-stable1%5Bbot%5D", slow_bot)
        with self.assertRaisesRegex(gate.GateError, "Timed out"):
            self.wait()
        self.assertEqual(self.sleeps, [])

    def test_redirect_handler_is_installed_and_refuses_token_forwarding(self):
        self.assertTrue(any(isinstance(handler, gate.NoRedirect) for handler in gate.OPENER.handlers))
        handler = gate.NoRedirect()
        request = urllib.request.Request("https://api.github.com", headers={"Authorization": "Bearer secret"})
        for code in (301, 302, 303, 307, 308):
            with self.subTest(code=code):
                self.assertIsNone(handler.redirect_request(request, None, code, "redirect", {},
                                                          "https://evil.example"))

    def test_cli_success_and_failure_exit_codes(self):
        os.environ.update(GITHUB_REPOSITORY=REPO, GITHUB_SHA=SHA, GITHUB_TOKEN="test-token")
        self.queue(page_path(), green())
        self.assertEqual(gate.main(), 0)
        self.queue(page_path(), [status(CONTEXTS[0], "failure")] + green())
        self.assertEqual(gate.main(), 1)
        self.assertIn("::error::GitLab integration verdict failed", self.errors.getvalue())
        self.assertNotIn("test-token", self.output.getvalue() + self.errors.getvalue())

    def test_cli_rejects_missing_token_non_sha_refs_and_invalid_repositories(self):
        original = {"GITHUB_REPOSITORY": REPO, "GITHUB_SHA": SHA, "GITHUB_TOKEN": "test-token"}
        for change in ({"GITHUB_TOKEN": ""}, {"GITHUB_SHA": "main"},
                       {"GITHUB_SHA": SHA + "/statuses"}, {"GITHUB_REPOSITORY": ""},
                       {"GITHUB_REPOSITORY": REPO + "?ref=other"}):
            with self.subTest(change=change):
                os.environ.update(original, **change)
                self.assertEqual(gate.main(), 1)
        self.assertEqual(self.requests, [])

    def test_cli_reports_summary_write_errors(self):
        os.environ.update(GITHUB_REPOSITORY=REPO, GITHUB_SHA=SHA, GITHUB_TOKEN="test-token")
        self.queue(page_path(), green())
        with tempfile.TemporaryDirectory() as directory:
            os.environ["GITHUB_STEP_SUMMARY"] = directory
            self.assertEqual(gate.main(), 1)
        self.assertIn("::error::", self.errors.getvalue())


if __name__ == "__main__":
    unittest.main()
