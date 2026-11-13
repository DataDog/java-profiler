# Copyright 2026, Datadog, Inc.
"""API-layer tests for the Bits review gate GitHubClient.

Pagination, retries, fail-closed API-error handling and read-token
separation, plus the shared fake transport's call recording, the
normalization/validation wiring of the snapshot seam — all hermetic
through the fake transport, with no network and no credentials.
"""

import contextlib
import io
import json
import os
import sys
import tempfile
import time
import unittest
import unittest.mock
import urllib.error
import urllib.request

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
import bits_review_gate as gate  # noqa: E402
import bits_review_gate_policy as policy  # noqa: E402

import bits_review_gate_testlib as testlib  # noqa: E402

REPO = "DataDog/java-profiler"
API = "https://api.example.test"
GRAPHQL = "https://api.example.test/graphql"
GITHUB_TOKEN = "gh-read-token"
STATUS_TOKEN = "status-write-token"
SHA = "1" * 40
PR985_HEAD = "1dcc3fa57582f2b595403f2b6a54e4464f352223"
PR968_HEAD = "1115eb583f475b62544d634bb12bf750ae913e04"
PULLS_URL = "%s/repos/%s/pulls?state=open&base=main&per_page=100" % (API, REPO)
STATUSES_URL = "%s/repos/%s/commits/%s/statuses" % (API, REPO, SHA)


PR_URL = "%s/repos/%s/pulls/985" % (API, REPO)


class FakeResponse:
    """A recorded HTTP response: status, bytes body, optional Link header."""

    def __init__(self, status, body=b"[]", link=None):
        self.status = status
        self._body = body if isinstance(body, bytes) else json.dumps(body).encode("utf-8")
        self.headers = {"Link": link} if link else {}

    def read(self):
        return self._body


class FakeStatusResponse(FakeResponse):
    """A non-2xx response delivered as a normal return, carrying headers."""

    def __init__(self, status, headers):
        super().__init__(status, [])
        self.headers = headers


class ClosingResponse(FakeResponse):
    """A fake response recording whether its close() ran."""

    def __init__(self, status, body=b"[]"):
        super().__init__(status, body)
        self.closed = False

    def close(self):
        self.closed = True


class RecordingHTTPError(urllib.error.HTTPError):
    """An HTTPError recording whether its close() ran."""

    def __init__(self, url, code, msg, hdrs, fp):
        super().__init__(url, code, msg, hdrs, fp)
        self.closed = False

    def close(self):
        self.closed = True
        super().close()


def make_client(transport):
    return gate.GitHubClient(REPO, transport=transport, env={
        "GITHUB_API_URL": API, "GITHUB_GRAPHQL_URL": GRAPHQL,
        "GITHUB_TOKEN": GITHUB_TOKEN, "STATUS_TOKEN": STATUS_TOKEN})


def reviews_page(nodes, has_next=False, cursor="cursor-1"):
    return {"data": {"repository": {"pullRequest": {"reviews": {
        "nodes": nodes,
        "pageInfo": {"hasNextPage": has_next, "endCursor": cursor}}}}}}


class FakeTransportRecordingTest(unittest.TestCase):
    """The shared fake transport records calls and surfaces queued failures."""

    def test_records_calls_and_rejects_unexpected_ones(self):
        transport = testlib.FakeTransport([OSError("socket reset")])
        request = urllib.request.Request(PULLS_URL)
        with self.assertRaises(OSError):
            transport(request)
        with self.assertRaises(AssertionError):
            transport(request)
        self.assertEqual(len(transport.calls), 2)

    def test_call_sequence_is_recorded_in_order(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, reviews_page([], has_next=True)),
            FakeResponse(200, reviews_page([])),
        ])
        nodes = make_client(transport).fetch_reviews(985)
        self.assertEqual(nodes, [])
        after = [json.loads(call.data)["variables"]["after"] for call in transport.calls]
        self.assertEqual(after, [None, "cursor-1"])


class RestPaginationTest(unittest.TestCase):
    """REST list endpoints are consumed page by page, following Link."""

    def test_multi_page_pr_list_is_fully_consumed(self):
        page2_url = PULLS_URL + "&page=2"
        page1 = [{"number": 985}, {"number": 968, "draft": True}]
        link = '<%s>; rel="next", <%s&page=3>; rel="last"' % (page2_url, PULLS_URL)
        transport = testlib.FakeTransport([
            FakeResponse(200, page1, link=link),
            FakeResponse(200, [{"number": 7}]),
        ])
        prs = make_client(transport).list_open_main_prs()
        self.assertEqual(prs, [{"number": 985}, {"number": 968, "draft": True}, {"number": 7}])
        self.assertEqual([call.full_url for call in transport.calls], [PULLS_URL, page2_url])

    def test_page_without_next_link_ends_pagination(self):
        transport = testlib.FakeTransport([FakeResponse(200, [{"number": 1}])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [{"number": 1}])
        self.assertEqual(len(transport.calls), 1)

    def test_statuses_are_paginated_fully(self):
        page2_url = STATUSES_URL + "?page=2"
        transport = testlib.FakeTransport([
            FakeResponse(200, [{"id": 1}], link='<%s>; rel="next"' % page2_url),
            FakeResponse(200, [{"id": 2}]),
        ])
        self.assertEqual(make_client(transport).read_statuses(SHA), [{"id": 1}, {"id": 2}])
        self.assertEqual([call.full_url for call in transport.calls], [STATUSES_URL, page2_url])

    def test_cross_origin_next_url_fails_closed_without_a_request(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [{"number": 1}],
                         link='<https://evil.example.test/repos/x>; rel="next"')])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_relative_next_url_fails_closed(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, [{"number": 1}], link='</repos/x?page=2>; rel="next"')])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_degenerate_empty_next_url_resolves_to_no_next_link(self):
        self.assertIsNone(gate._next_link('<>; rel="next"', API))

    def test_degenerate_next_url_page_yields_items_with_one_call(self):
        transport = testlib.FakeTransport(
            [FakeResponse(200, [{"number": 1}], link='<>; rel="next"')])
        self.assertEqual(make_client(transport).list_open_main_prs(), [{"number": 1}])
        self.assertEqual(len(transport.calls), 1)

    def test_degenerate_next_part_is_skipped_for_a_later_valid_next(self):
        page2_url = PULLS_URL + "&page=2"
        transport = testlib.FakeTransport([
            FakeResponse(200, [{"number": 1}],
                         link='<>; rel="next", <%s>; rel="next"' % page2_url),
            FakeResponse(200, [{"number": 2}])])
        self.assertEqual(make_client(transport).list_open_main_prs(),
                         [{"number": 1}, {"number": 2}])
        self.assertEqual([call.full_url for call in transport.calls], [PULLS_URL, page2_url])

    def test_comma_inside_a_next_url_does_not_break_parsing(self):
        page2_url = PULLS_URL + "&page=2,cursor=a,b"
        transport = testlib.FakeTransport([
            FakeResponse(200, [{"number": 1}], link='<%s>; rel="next"' % page2_url),
            FakeResponse(200, [{"number": 2}])])
        self.assertEqual(make_client(transport).list_open_main_prs(),
                         [{"number": 1}, {"number": 2}])
        self.assertEqual([call.full_url for call in transport.calls], [PULLS_URL, page2_url])


class GraphqlPaginationTest(unittest.TestCase):
    """Review pages are followed until pageInfo.hasNextPage is false."""

    def test_multi_page_reviews_are_fully_consumed(self):
        first = testlib.build_review_node(databaseId=1)
        second = testlib.build_review_node(databaseId=2)
        transport = testlib.FakeTransport([
            FakeResponse(200, reviews_page([first], has_next=True, cursor="cursor-1")),
            FakeResponse(200, reviews_page([second])),
        ])
        self.assertEqual(make_client(transport).fetch_reviews(985), [first, second])
        after = [json.loads(call.data)["variables"]["after"] for call in transport.calls]
        self.assertEqual(after, [None, "cursor-1"])

    def test_single_page_stops_when_has_next_page_is_false(self):
        node = testlib.build_review_node()
        transport = testlib.FakeTransport([FakeResponse(200, reviews_page([node]))])
        self.assertEqual(make_client(transport).fetch_reviews({"number": 985}), [node])
        self.assertEqual(json.loads(transport.calls[0].data)["variables"]["number"], 985)
        self.assertEqual(len(transport.calls), 1)

    def test_query_requests_exactly_the_contract_fields(self):
        transport = testlib.FakeTransport([FakeResponse(200, reviews_page([]))])
        make_client(transport).fetch_reviews(985)
        query = json.loads(transport.calls[0].data)["query"]
        for field in ("databaseId", "state", "body", "submittedAt", "lastEditedAt",
                      "commit { oid }", "__typename", "login",
                      "on Bot { databaseId }", "on User { databaseId }"):
            self.assertIn(field, query)
        self.assertNotIn("userContentEdits", query)
        self.assertNotIn("includesCreatedEdit", query)

    def test_invalid_pr_number_fails_without_a_request(self):
        for bad in ("985", 0, True):
            with self.subTest(bad=bad):
                transport = testlib.FakeTransport([])
                with self.assertRaises(gate.ApiError):
                    make_client(transport).fetch_reviews(bad)
                self.assertEqual(transport.calls, [])


class RetryPolicyTest(unittest.TestCase):
    """Network errors, 5xx and rate-limited 403/429 retry up to three
    attempts; every other 4xx never."""

    def test_5xx_is_retried_exactly_three_times_then_fails(self):
        transport = testlib.FakeTransport([FakeResponse(500)] * 3)
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 3)

    def test_5xx_retry_can_succeed_on_a_later_attempt(self):
        transport = testlib.FakeTransport([FakeResponse(503), FakeResponse(200, [])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(len(transport.calls), 2)

    def test_4xx_response_is_not_retried(self):
        transport = testlib.FakeTransport([FakeResponse(404)])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_network_error_is_retried_until_success(self):
        transport = testlib.FakeTransport([OSError("connection reset"), FakeResponse(200, [])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(len(transport.calls), 2)

    def test_network_error_exhausts_attempts_then_fails(self):
        transport = testlib.FakeTransport([OSError("connection reset")] * 3)
        with self.assertRaises(gate.ApiError):
            make_client(transport).read_statuses(SHA)
        self.assertEqual(len(transport.calls), 3)

    def test_http_errors_follow_the_same_retry_policy(self):
        cases = [
            (urllib.error.HTTPError(PULLS_URL, 403, "Forbidden", None, None), 1),
            (urllib.error.HTTPError(PULLS_URL, 502, "Bad Gateway", None, None), 3),
        ]
        for error, attempts in cases:
            with self.subTest(code=error.code, attempts=attempts):
                transport = testlib.FakeTransport([error] * attempts)
                with self.assertRaises(gate.ApiError):
                    make_client(transport).list_open_main_prs()
                self.assertEqual(len(transport.calls), attempts)
        recovered = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 502, "Bad Gateway", None, None),
            FakeResponse(200, [])])
        self.assertEqual(make_client(recovered).list_open_main_prs(), [])
        self.assertEqual(len(recovered.calls), 2)

    def test_429_http_error_with_retry_after_is_retried_then_succeeds(self):
        transport = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 429, "Too Many Requests",
                                   {"Retry-After": "0"}, None),
            FakeResponse(200, [])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(len(transport.calls), 2)

    def test_429_non_2xx_response_with_retry_after_is_retried_then_succeeds(self):
        transport = testlib.FakeTransport([
            FakeStatusResponse(429, {"Retry-After": "0"}),
            FakeResponse(200, [])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(len(transport.calls), 2)

    def test_rate_limited_403_exhausts_the_shared_budget(self):
        transport = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 403, "Forbidden",
                                   {"x-ratelimit-remaining": "0"}, None)] * 3)
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 3)

    def test_429_without_a_header_signal_fails_fast(self):
        transport = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 429, "Too Many Requests", None, None)])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_rate_limit_headers_match_case_insensitively(self):
        retried = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 429, "Too Many Requests",
                                   {"RETRY-AFTER": "0"}, None),
            FakeResponse(200, [])])
        self.assertEqual(make_client(retried).list_open_main_prs(), [])
        self.assertEqual(len(retried.calls), 2)
        exhausted = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 403, "Forbidden",
                                   {"X-RateLimit-Remaining": "0"}, None)] * 3)
        with self.assertRaises(gate.ApiError):
            make_client(exhausted).list_open_main_prs()
        self.assertEqual(len(exhausted.calls), 3)

    def test_retry_after_is_clamped_to_the_cap(self):
        # With the 300 s honor cap, a window beyond it fails fast instead
        # of sleeping: exactly one attempt, RateLimitError, no long sleep.
        with unittest.mock.patch.object(gate.time, "sleep") as slept:
            transport = testlib.FakeTransport([
                urllib.error.HTTPError(PULLS_URL, 429, "Too Many Requests",
                                       {"Retry-After": "3600"}, None)])
            with self.assertRaises(gate.RateLimitError):
                make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)
        self.assertEqual(slept.call_args_list, [])

    def test_negative_retry_after_is_clamped_to_zero(self):
        # A hostile Retry-After must reach time.sleep only after the
        # clamp: time.sleep(-1) would raise ValueError outside both
        # fail-closed handlers.
        with unittest.mock.patch.object(gate.time, "sleep") as slept:
            transport = testlib.FakeTransport([
                urllib.error.HTTPError(PULLS_URL, 429, "Too Many Requests",
                                       {"Retry-After": "-1"}, None),
                FakeResponse(200, [])])
            self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(slept.call_args_list, [unittest.mock.call(0)])

    def test_plain_403_with_retry_after_is_not_retried(self):
        # A 403 without x-ratelimit-remaining 0 is never classified as a
        # rate limit, whatever Retry-After header it carries.
        transport = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 403, "Forbidden",
                                   {"Retry-After": "5"}, None)])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_403_with_retry_after_and_exhausted_remaining_is_retried(self):
        # The genuine-rate-limit path: a 403 with both signals honors the
        # delay and retries.
        with unittest.mock.patch.object(gate.time, "sleep") as slept:
            transport = testlib.FakeTransport([
                urllib.error.HTTPError(PULLS_URL, 403, "Forbidden",
                                       {"Retry-After": "0",
                                        "x-ratelimit-remaining": "0"}, None),
                FakeResponse(200, [])])
            self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(slept.call_args_list, [unittest.mock.call(0)])

    def test_429_with_remaining_zero_but_no_retry_after_fails_fast(self):
        # A 429 needs a Retry-After header to count as rate-limited;
        # remaining 0 alone must not make it retry.
        transport = testlib.FakeTransport([
            urllib.error.HTTPError(PULLS_URL, 429, "Too Many Requests",
                                   {"x-ratelimit-remaining": "0"}, None)])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_retry_after_600_exceeds_the_honor_cap_and_fails_fast(self):
        transport = testlib.FakeTransport([
            FakeStatusResponse(429, {"Retry-After": "600"})])
        with self.assertRaises(gate.RateLimitError) as caught:
            make_client(transport).list_open_main_prs()
        self.assertIn("rate limit", str(caught.exception))
        self.assertEqual(len(transport.calls), 1)

    def test_rate_limit_reset_beyond_the_cap_fails_fast(self):
        transport = testlib.FakeTransport([
            FakeStatusResponse(403, {"x-ratelimit-remaining": "0",
                                     "x-ratelimit-reset": str(int(time.time()) + 600)})])
        with self.assertRaises(gate.RateLimitError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_rate_limit_reset_within_the_cap_is_honored(self):
        with unittest.mock.patch.object(gate.time, "sleep") as slept:
            transport = testlib.FakeTransport([
                FakeStatusResponse(403, {"x-ratelimit-remaining": "0",
                                         "x-ratelimit-reset": str(int(time.time()) + 10)}),
                FakeResponse(200, [])])
            self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(len(transport.calls), 2)
        slept_seconds = slept.call_args_list[0][0][0]
        self.assertGreaterEqual(slept_seconds, 9.0)
        self.assertLessEqual(slept_seconds, 10.0)

    def test_rate_limit_reset_in_the_past_clamps_to_zero(self):
        with unittest.mock.patch.object(gate.time, "sleep") as slept:
            transport = testlib.FakeTransport([
                FakeStatusResponse(403, {"x-ratelimit-remaining": "0",
                                         "x-ratelimit-reset": str(int(time.time()) - 30)}),
                FakeResponse(200, [])])
            self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(slept.call_args_list, [unittest.mock.call(0)])

    def test_in_cap_retry_after_is_honored(self):
        with unittest.mock.patch.object(gate.time, "sleep") as slept:
            transport = testlib.FakeTransport([
                FakeStatusResponse(429, {"Retry-After": "120"}),
                FakeResponse(200, [])])
            self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(slept.call_args_list, [unittest.mock.call(120)])

    def test_rate_limit_exhaustion_raises_a_named_rate_limit_error(self):
        transport = testlib.FakeTransport([
            FakeStatusResponse(403, {"x-ratelimit-remaining": "0"})] * 3)
        with self.assertRaises(gate.RateLimitError) as caught:
            make_client(transport).list_open_main_prs()
        self.assertIn("rate limit for %s after %d attempts" % (PULLS_URL, gate.MAX_ATTEMPTS),
                      str(caught.exception))
        self.assertEqual(len(transport.calls), 3)

    def test_non_integer_retry_after_falls_back_to_default_backoff(self):
        with unittest.mock.patch.object(gate.time, "sleep") as slept:
            transport = testlib.FakeTransport([
                urllib.error.HTTPError(PULLS_URL, 429, "Too Many Requests",
                                       {"Retry-After": "soon"}, None),
                FakeResponse(200, [])])
            self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(slept.call_args_list,
                         [unittest.mock.call(gate._RETRY_BACKOFF_SECONDS)])


class BodyReadRetryTest(unittest.TestCase):
    """A transport failure during response-body read goes through the
    same retry and ApiError conversion as the request itself — it must
    never escape the transport handler."""

    def test_body_read_failure_is_retried_until_success(self):
        class FailingRead(FakeResponse):
            def __init__(self, failures):
                super().__init__(200, [])
                self.failures = failures

            def read(self):
                if self.failures:
                    self.failures -= 1
                    raise OSError("connection reset during body read")
                return self._body

        transport = testlib.FakeTransport([FailingRead(1), FakeResponse(200, [])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertEqual(len(transport.calls), 2)

    def test_body_read_failure_exhausts_attempts_and_fails_closed(self):
        class AlwaysFailingRead(FakeResponse):
            def read(self):
                raise OSError("connection reset during body read")

        transport = testlib.FakeTransport([AlwaysFailingRead(200, [])] * 3)
        with self.assertRaises(gate.ApiError):
            make_client(transport).read_statuses(SHA)
        self.assertEqual(len(transport.calls), 3)

    def test_non_retryable_4xx_body_read_failure_gets_exactly_one_attempt(self):
        class FailingRead(FakeResponse):
            def __init__(self, status):
                super().__init__(status, [])

            def read(self):
                raise OSError("connection reset during body read")

        transport = testlib.FakeTransport([FailingRead(404)])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 1)

    def test_retryable_5xx_body_read_failure_keeps_retrying(self):
        class FailingRead(FakeResponse):
            def __init__(self, status):
                super().__init__(status, [])

            def read(self):
                raise OSError("connection reset during body read")

        transport = testlib.FakeTransport([FailingRead(503)] * 3)
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertEqual(len(transport.calls), 3)


class ResponseClosingTest(unittest.TestCase):
    """Every response opened in _fetch is closed on every exit path."""

    def test_success_path_closes_the_response(self):
        response = ClosingResponse(200, [])
        transport = testlib.FakeTransport([response])
        make_client(transport).list_open_main_prs()
        self.assertTrue(response.closed)

    def test_non_2xx_path_closes_the_response(self):
        response = ClosingResponse(404)
        transport = testlib.FakeTransport([response])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertTrue(response.closed)

    def test_http_error_path_closes_the_error(self):
        error = RecordingHTTPError(PULLS_URL, 404, "Not Found", None, None)
        transport = testlib.FakeTransport([error])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()
        self.assertTrue(error.closed)

    def test_retried_http_error_closes_the_error(self):
        error = RecordingHTTPError(PULLS_URL, 502, "Bad Gateway", None, None)
        transport = testlib.FakeTransport([error, FakeResponse(200, [])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertTrue(error.closed)

    def test_failed_body_read_still_closes_the_response(self):
        class FailingRead(ClosingResponse):
            def read(self):
                raise OSError("connection reset during body read")

        response = FailingRead(200, [])
        transport = testlib.FakeTransport([response, FakeResponse(200, [])])
        self.assertEqual(make_client(transport).list_open_main_prs(), [])
        self.assertTrue(response.closed)


class MatchesDecisionTest(unittest.TestCase):
    """The suppression predicate requires every write-payload field to
    match, the persisted context included."""

    def _decision(self):
        return {"state": "success", "reason": "pass", "governing_pr": 968,
                "description": "Bits review: pass",
                "target_url": "https://example.test/pr/968",
                "context": policy.STATUS_CONTEXT}

    def _status(self, **overrides):
        status = {"state": "success", "description": "Bits review: pass",
                  "target_url": "https://example.test/pr/968",
                  "context": policy.STATUS_CONTEXT}
        status.update(overrides)
        return status

    def test_equal_status_matches(self):
        self.assertTrue(gate._matches_decision(self._status(), self._decision()))

    def test_foreign_context_never_matches(self):
        self.assertFalse(gate._matches_decision(
            self._status(context="bits-review/head-evil"), self._decision()))


class GraphqlFailClosedTest(unittest.TestCase):
    """GraphQL errors and missing structure never yield a partial list."""

    def test_errors_with_partial_data_fail(self):
        page = reviews_page([testlib.build_review_node()])
        page["errors"] = [{"message": "Something went wrong"}]
        transport = testlib.FakeTransport([FakeResponse(200, page)])
        with self.assertRaises(gate.ApiError):
            make_client(transport).fetch_reviews(985)
        self.assertEqual(len(transport.calls), 1)

    def test_missing_response_structure_fails(self):
        def drop_reviews(page):
            page["data"]["repository"]["pullRequest"].pop("reviews")
        breakers = [
            lambda p: p.pop("data"),
            lambda p: p["data"].pop("repository"),
            lambda p: p["data"]["repository"].pop("pullRequest"),
            drop_reviews,
            lambda p: p["data"]["repository"]["pullRequest"]["reviews"].pop("nodes"),
            lambda p: p["data"]["repository"]["pullRequest"]["reviews"].pop("pageInfo"),
        ]
        for breaker in breakers:
            with self.subTest(breaker=breaker):
                page = reviews_page([testlib.build_review_node()])
                breaker(page)
                transport = testlib.FakeTransport([FakeResponse(200, page)])
                with self.assertRaises(gate.ApiError):
                    make_client(transport).fetch_reviews(985)

    def test_missing_end_cursor_on_nonfinal_page_fails(self):
        page = reviews_page([testlib.build_review_node()], has_next=True, cursor=None)
        transport = testlib.FakeTransport([FakeResponse(200, page)])
        with self.assertRaises(gate.ApiError):
            make_client(transport).fetch_reviews(985)

    def test_malformed_json_fails_closed(self):
        readers = [lambda c: c.list_open_main_prs(),
                   lambda c: c.read_statuses(SHA),
                   lambda c: c.fetch_reviews(985)]
        for reader in readers:
            with self.subTest(reader=reader):
                transport = testlib.FakeTransport([FakeResponse(200, b"<html>not json")])
                with self.assertRaises(gate.ApiError):
                    reader(make_client(transport))

    def test_rest_non_array_body_fails(self):
        transport = testlib.FakeTransport([FakeResponse(200, {"message": "nope"})])
        with self.assertRaises(gate.ApiError):
            make_client(transport).list_open_main_prs()


class ReadTokenTest(unittest.TestCase):
    """Reads carry GITHUB_TOKEN only; STATUS_TOKEN never appears."""

    def _recorded_reads(self):
        transport = testlib.FakeTransport([
            FakeResponse(200, []),
            FakeResponse(200, reviews_page([])),
            FakeResponse(200, []),
        ])
        client = make_client(transport)
        client.list_open_main_prs()
        client.fetch_reviews(985)
        client.read_statuses(SHA)
        return transport

    def test_read_urls_use_the_env_base_urls(self):
        transport = self._recorded_reads()
        self.assertEqual([call.full_url for call in transport.calls],
                         [PULLS_URL, GRAPHQL, STATUSES_URL])

    def test_every_read_carries_github_token_and_never_status_token(self):
        transport = self._recorded_reads()
        self.assertEqual(len(transport.calls), 3)
        for call in transport.calls:
            self.assertEqual(call.headers.get("Authorization"), "Bearer " + GITHUB_TOKEN)
            for value in call.headers.values():
                self.assertNotIn(STATUS_TOKEN, value)

    def test_missing_github_token_sends_no_authorization(self):
        transport = testlib.FakeTransport([FakeResponse(200, [])])
        client = gate.GitHubClient(REPO, transport=transport, env={
            "GITHUB_API_URL": API, "GITHUB_GRAPHQL_URL": GRAPHQL, "STATUS_TOKEN": STATUS_TOKEN})
        client.list_open_main_prs()
        self.assertNotIn("Authorization", transport.calls[0].headers)

    def test_default_base_urls_without_env_entries(self):
        transport = testlib.FakeTransport([FakeResponse(200, []), FakeResponse(200, reviews_page([]))])
        client = gate.GitHubClient(REPO, transport=transport, env={})
        client.list_open_main_prs()
        client.fetch_reviews(985)
        self.assertTrue(transport.calls[0].full_url.startswith("https://api.github.com/repos/"))
        self.assertEqual(transport.calls[1].full_url, "https://api.github.com/graphql")


class HelperBuilderTest(unittest.TestCase):
    """The extended scaffold builders emit exactly their fields."""

    def test_pr_record_builder_emits_exactly_the_gate_fields(self):
        pr = testlib.build_pr_record(number=968, sha=PR968_HEAD)
        self.assertEqual(pr, {"number": 968, "state": "open",
                              "head": {"sha": PR968_HEAD}, "base": {"ref": "main"}})
        self.assertEqual(testlib.build_pr_record()["head"]["sha"], "1" * 40)

    def test_fixture_node_wraps_the_single_mapping_with_overrides(self):
        rest = testlib.load_review_fixture("pr968")
        node = testlib.fixture_node("pr968", lastEditedAt="2026-06-30T08:48:47Z")
        self.assertEqual(node["body"], rest["body"])
        self.assertEqual(node["commit"]["oid"], rest["commit_id"])
        self.assertEqual(node["lastEditedAt"], "2026-06-30T08:48:47Z")


class NormalizeReviewTest(unittest.TestCase):
    """normalize_review maps GraphQL nodes to the contract's records.

    Every author value comes from the GraphQL author fields and is chosen
    distinct from any REST fixture value, so a mapping that consulted a
    REST-named field cannot pass. No REST/GraphQL equivalence is claimed."""

    def test_distinct_author_types_map_to_distinct_records(self):
        authors = [
            {"__typename": "Bot", "login": "graphql-bot[bot]", "databaseId": 555001},
            {"__typename": "User", "login": "graphql-user", "databaseId": 555002},
            {"__typename": "Organization", "login": "graphql-org", "databaseId": 555003},
            None,
        ]
        records = [
            gate.normalize_review(testlib.build_review_node(author=author, databaseId=61 + i))
            for i, author in enumerate(authors)
        ]
        self.assertEqual([r["author_typename"] for r in records],
                         ["Bot", "User", "Organization", None])
        self.assertEqual([r["author_id"] for r in records], [555001, 555002, 555003, None])
        self.assertEqual([r["author_login"] for r in records],
                         ["graphql-bot[bot]", "graphql-user", "graphql-org", None])

    def test_rest_named_fields_are_never_consulted(self):
        node = testlib.build_review_node(
            databaseId=555004,
            submittedAt="2026-05-05T05:05:05Z",
            lastEditedAt="2026-05-05T06:06:06Z",
            commit={"oid": PR968_HEAD},
            author={"__typename": "Bot", "login": "graphql-only-bot[bot]", "databaseId": 555005},
            user={"id": 1, "type": "User", "login": "rest-user"},
            commit_id="rest-commit-id",
            submitted_at="rest-submitted-at",
            last_edited_at="rest-edited-at",
        )
        record = gate.normalize_review(node)
        self.assertEqual(record["id"], 555004)
        self.assertEqual(record["author_typename"], "Bot")
        self.assertEqual(record["author_id"], 555005)
        self.assertEqual(record["author_login"], "graphql-only-bot[bot]")
        self.assertEqual(record["commit_oid"], PR968_HEAD)
        self.assertEqual(record["submitted_at"], "2026-05-05T05:05:05Z")
        self.assertEqual(record["last_edited_at"], "2026-05-05T06:06:06Z")

    def test_fixture_nodes_round_trip_to_the_exact_contract_record(self):
        for pr in ("pr985", "pr968"):
            with self.subTest(pr=pr):
                rest = testlib.load_review_fixture(pr)
                record = gate.normalize_review(testlib.rest_review_to_node(rest))
                self.assertEqual(record, testlib.build_review_record(
                    id=rest["id"], author_typename=rest["user"]["type"],
                    author_id=rest["user"]["id"], author_login=rest["user"]["login"],
                    state=rest["state"], body=rest["body"],
                    commit_oid=rest["commit_id"], submitted_at=rest["submitted_at"],
                    last_edited_at=None))

    def test_raw_last_edited_at_is_retained_verbatim(self):
        for raw in ("2026-06-30T08:48:47Z", "not-a-timestamp", ""):
            with self.subTest(raw=raw):
                record = gate.normalize_review(testlib.build_review_node(lastEditedAt=raw))
                self.assertEqual(record["last_edited_at"], raw)
                self.assertIsNot(record["last_edited_at"], True)

    def test_null_and_non_object_authors_map_to_null_author_fields(self):
        for author in (None, {}, "not-an-object"):
            with self.subTest(author=author):
                record = gate.normalize_review(testlib.build_review_node(author=author))
                self.assertIsNone(record["author_typename"])
                self.assertIsNone(record["author_id"])
                self.assertIsNone(record["author_login"])

    def test_non_object_node_maps_to_a_fail_closed_empty_record(self):
        record = gate.normalize_review("not-a-node")
        self.assertEqual(record, testlib.build_review_record(
            id=None, author_typename=None, author_id=None, author_login=None,
            state=None, body=None, commit_oid=None, submitted_at=None,
            last_edited_at=None))
        self.assertEqual(policy.outcome([record], head=PR968_HEAD), "invalid-input")


class PaginationCapTest(unittest.TestCase):
    """Both pagination loops fail closed past MAX_FETCH_PAGES — the read
    is never truncated and never hangs. Pre-fix failure mode: without the
    cap, the cap-th page's 'unexpected transport call' AssertionError is
    retried by _fetch, so the message and call-count assertions fail."""

    def test_reviews_pagination_past_the_cap_fails_closed(self):
        pages = [FakeResponse(200, reviews_page([], has_next=True, cursor="c%d" % i))
                 for i in range(gate.MAX_FETCH_PAGES)]
        transport = testlib.FakeTransport(pages)
        with self.assertRaises(gate.ApiError) as caught:
            make_client(transport).fetch_reviews(985)
        self.assertIn("reviews pagination", str(caught.exception))
        self.assertEqual(len(transport.calls), gate.MAX_FETCH_PAGES)

    def test_rest_pagination_past_the_cap_fails_closed(self):
        def page(i):
            url = PULLS_URL + "&page=%d" % (i + 2,)
            return FakeResponse(200, [{"number": i}], link='<%s>; rel="next"' % url)
        transport = testlib.FakeTransport([page(i) for i in range(gate.MAX_FETCH_PAGES)])
        with self.assertRaises(gate.ApiError) as caught:
            make_client(transport).list_open_main_prs()
        self.assertIn("REST pagination", str(caught.exception))
        self.assertEqual(len(transport.calls), gate.MAX_FETCH_PAGES)

    def test_read_ending_on_the_cap_th_page_succeeds(self):
        pages = [FakeResponse(200, reviews_page([], has_next=True, cursor="c%d" % i))
                 for i in range(gate.MAX_FETCH_PAGES - 1)]
        pages.append(FakeResponse(200, reviews_page([])))
        transport = testlib.FakeTransport(pages)
        self.assertEqual(make_client(transport).fetch_reviews(985), [])
        self.assertEqual(len(transport.calls), gate.MAX_FETCH_PAGES)

class SnapshotReadTest(unittest.TestCase):
    """The fetch path wires the T1 validators in, fail-closed: invalid
    possible candidates and malformed PR records are flagged, never
    skipped, so an older PASS is never uncovered."""

    def _read(self, open_prs, review_pages, head=PR968_HEAD):
        transport = testlib.FakeTransport(
            [FakeResponse(200, open_prs)] + list(review_pages))
        return gate.read_sha_snapshot(head, make_client(transport)), transport

    def test_fixture_reviews_round_trip_and_classify_through_the_fetch_path(self):
        for pr, number, head, expected in (
                ("pr968", 968, PR968_HEAD, "pass"), ("pr985", 985, PR985_HEAD, "fail")):
            with self.subTest(pr=pr):
                rest = testlib.load_review_fixture(pr)
                snapshot, _ = self._read(
                    [testlib.build_pr_record(number=number, sha=head)],
                    [FakeResponse(200, reviews_page([testlib.rest_review_to_node(rest)]))],
                    head=head)
                self.assertEqual(snapshot["outcomes"], {number: expected})
                self.assertEqual(snapshot["invalid_input"], [])
                self.assertEqual(snapshot["api_error"], [])
                record = snapshot["reviews"][number][0]
                self.assertEqual(record["body"], rest["body"])
                self.assertEqual(record["commit_oid"], rest["commit_id"])
                self.assertEqual(record["submitted_at"], rest["submitted_at"])
                self.assertIsNone(record["last_edited_at"])

    def test_each_invalid_input_shape_flags_the_pr_outcome_over_an_older_pass(self):
        older_pass = testlib.fixture_node("pr968")
        marked_body = testlib.load_review_fixture("pr985")["body"]
        shapes = {
            "state": {"state": "CHANGED_REQUESTED"},
            "submitted-at": {"submittedAt": "garbage"},
            "null-submitted-at": {"submittedAt": None},
            "last-edited-at": {"lastEditedAt": "not-a-timestamp", "body": "plain bot text"},
            "id": {"databaseId": 0},
            "string-id": {"databaseId": "5873000001"},
            "bot-database-id": {"author": {"__typename": "Bot", "login": "graphql-bot[bot]", "databaseId": None}},
            "body": {"body": 123},
            "null-author": {"author": None},
            "unknown-author": {"author": {"__typename": "Organization", "login": "graphql-org"}},
            "commit-oid": {"commit": {"oid": "not-hex"}},
        }
        for name, overrides in shapes.items():
            with self.subTest(shape=name):
                node = {"databaseId": 5873000001, "submittedAt": "2026-11-12T12:00:00Z",
                        "commit": {"oid": PR968_HEAD}, "body": marked_body}
                node.update(overrides)
                broken = testlib.build_review_node(**node)
                snapshot, _ = self._read(
                    [testlib.build_pr_record(number=968, sha=PR968_HEAD)],
                    [FakeResponse(200, reviews_page([older_pass, broken]))])
                self.assertEqual(snapshot["outcomes"], {968: "invalid-input"})
                self.assertEqual(snapshot["invalid_input"], ["pr-968"])
                self.assertEqual(snapshot["api_error"], [])

    def test_unrelated_invalid_bot_node_is_ignored(self):
        older_pass = testlib.fixture_node("pr968")
        unrelated = testlib.build_review_node(
            databaseId=5873000002, submittedAt="2026-11-12T14:00:00Z",
            commit={"oid": PR968_HEAD}, body="LGTM", state="garbage")
        snapshot, _ = self._read(
            [testlib.build_pr_record(number=968, sha=PR968_HEAD)],
            [FakeResponse(200, reviews_page([older_pass, unrelated]))])
        self.assertEqual(snapshot["outcomes"], {968: "pass"})
        self.assertEqual(snapshot["invalid_input"], [])

    def test_malformed_known_user_review_is_ignored(self):
        older_pass = testlib.fixture_node("pr968")
        copied_markers = testlib.load_review_fixture("pr985")["body"]
        user = testlib.build_review_node(
            databaseId=5873000003, submittedAt="whenever", state="garbage",
            commit={"oid": PR968_HEAD}, body=copied_markers,
            author={"__typename": "User", "login": "graphql-user", "databaseId": 555006})
        snapshot, _ = self._read(
            [testlib.build_pr_record(number=968, sha=PR968_HEAD)],
            [FakeResponse(200, reviews_page([older_pass, user]))])
        self.assertEqual(snapshot["outcomes"], {968: "pass"})
        self.assertEqual(snapshot["invalid_input"], [])
        self.assertEqual(snapshot["api_error"], [])

    def test_malformed_pr_record_flags_the_snapshot_invalid_input(self):
        good = testlib.build_pr_record(number=968, sha=PR968_HEAD)
        older_pass = testlib.fixture_node("pr968")
        shapes = [
            ("number", testlib.build_pr_record(number=0, sha=PR968_HEAD)),
            ("head.sha", testlib.build_pr_record(number=7, sha="abc")),
            ("head.sha", testlib.build_pr_record(number=7, sha=PR985_HEAD.upper())),
            ("base.ref", {"number": 7, "head": {"sha": PR968_HEAD}, "state": "open"}),
            ("state", testlib.build_pr_record(number=7, sha=PR968_HEAD, state=None)),
            ("record", "not-a-pr-record"),
        ]
        for token, malformed in shapes:
            with self.subTest(token=token, malformed=malformed):
                snapshot, transport = self._read(
                    [malformed, good],
                    [FakeResponse(200, reviews_page([older_pass]))])
                self.assertIn("pr-record:%s" % token, snapshot["invalid_input"])
                self.assertEqual(snapshot["prs"], [good])
                self.assertEqual(snapshot["outcomes"], {968: "pass"})
                # The malformed record triggers no review read of its own.
                self.assertEqual(len(transport.calls), 2)

    def test_only_p_h_members_are_fetched_and_evaluated(self):
        other_head = testlib.build_pr_record(number=985, sha=PR985_HEAD)
        member = testlib.build_pr_record(number=968, sha=PR968_HEAD)
        snapshot, transport = self._read(
            [other_head, member],
            [FakeResponse(200, reviews_page(
                [testlib.fixture_node("pr985", commit={"oid": PR968_HEAD})]))])
        self.assertEqual(snapshot["prs"], [member])
        self.assertEqual(snapshot["outcomes"], {968: "fail"})
        self.assertEqual(sorted(snapshot["reviews"]), [968])
        self.assertEqual(len(transport.calls), 2)
        self.assertEqual(json.loads(transport.calls[1].data)["variables"]["number"], 968)

    def test_empty_p_h_reads_cleanly(self):
        other_head = testlib.build_pr_record(number=985, sha=PR985_HEAD)
        snapshot, transport = self._read([other_head], [])
        self.assertEqual(snapshot["prs"], [])
        self.assertEqual(snapshot["reviews"], {})
        self.assertEqual(snapshot["outcomes"], {})
        self.assertEqual(snapshot["invalid_input"], [])
        self.assertEqual(snapshot["api_error"], [])
        self.assertEqual(len(transport.calls), 1)

    def test_pulls_failure_flags_api_error_without_review_reads(self):
        transport = testlib.FakeTransport([FakeResponse(500)] * 3)
        snapshot = gate.read_sha_snapshot(PR968_HEAD, make_client(transport))
        self.assertEqual(snapshot["api_error"], ["pulls"])
        self.assertEqual(snapshot["prs"], [])
        self.assertEqual(snapshot["reviews"], {})
        self.assertEqual(snapshot["outcomes"], {})
        self.assertEqual(len(transport.calls), 3)

    def test_review_fetch_failure_flags_that_pr_api_error(self):
        first = testlib.build_pr_record(number=968, sha=PR968_HEAD)
        second = testlib.build_pr_record(number=969, sha=PR968_HEAD)
        snapshot, transport = self._read(
            [first, second],
            [FakeResponse(500), FakeResponse(500), FakeResponse(500),
             FakeResponse(200, reviews_page([testlib.fixture_node("pr968")]))])
        self.assertEqual(snapshot["api_error"], ["pr-968/reviews"])
        self.assertEqual(snapshot["prs"], [first, second])
        self.assertEqual(snapshot["outcomes"], {968: "api-error", 969: "pass"})
        self.assertEqual(sorted(snapshot["reviews"]), [969])
        self.assertEqual(len(transport.calls), 5)


def resolve_env(event, **overrides):
    """The env of one resolve run: the shared client settings, the
    pull_request_target selector and, for workflow_run, its four
    workflow-run selectors."""
    env = {
        "GITHUB_EVENT_NAME": event,
        "GITHUB_REPOSITORY": REPO,
        "GITHUB_API_URL": API,
        "GITHUB_GRAPHQL_URL": GRAPHQL,
        "GITHUB_TOKEN": GITHUB_TOKEN,
        "GITHUB_PR_NUMBER": "985",
    }
    if event == "workflow_run":
        env.update({
            "GITHUB_HEAD_SHA": SHA,
            "GITHUB_HEAD_BRANCH": "patch-1",
            "GITHUB_HEAD_REPOSITORY": "some-fork/java-profiler",
            "GITHUB_PULL_REQUEST_NUMBERS": "[]",
        })
    env.update(overrides)
    return env


def open_main_pr(number, sha, head_repository=REPO, head_branch=None):
    """An open-main pulls-list record carrying the selector fields the
    resolver compares (head repository full name and head branch)."""
    pr = testlib.build_pr_record(number=number, sha=sha)
    pr["head"]["ref"] = head_branch or "pr-%d-head" % (number,)
    pr["head"]["repo"] = {"full_name": head_repository}
    return pr


class ResolveCommandTest(unittest.TestCase):
    """The resolve subcommand: env-only inputs, per-event SHA selection,
    validation, the 256 cap, dedupe and the JSON output."""

    def _run(self, transport, event, output=None, **overrides):
        env = resolve_env(event, **overrides)
        if output is not None:
            env["GITHUB_OUTPUT"] = output
        with contextlib.redirect_stdout(io.StringIO()) as captured:
            code = gate.main(["resolve"], env=env, transport=transport)
        return code, captured.getvalue()

    def _schedule(self, prs):
        return testlib.FakeTransport([FakeResponse(200, prs)])

    def test_workflow_run_fork_run_with_empty_pr_list_emits_run_head_and_all_open_main_heads(self):
        prs = [open_main_pr(968, PR968_HEAD), open_main_pr(985, PR985_HEAD)]
        code, out = self._run(self._schedule(prs), "workflow_run")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA, PR968_HEAD, PR985_HEAD]))

    def test_workflow_run_matches_open_main_prs_by_number(self):
        prs = [open_main_pr(968, PR968_HEAD), open_main_pr(985, PR985_HEAD)]
        code, out = self._run(self._schedule(prs), "workflow_run",
                               GITHUB_PULL_REQUEST_NUMBERS="[968]")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA, PR968_HEAD]))

    def test_workflow_run_matches_by_head_repository_and_branch(self):
        prs = [open_main_pr(968, PR968_HEAD, head_repository="some-fork/java-profiler",
                            head_branch="patch-1"),
               open_main_pr(985, PR985_HEAD)]
        code, out = self._run(self._schedule(prs), "workflow_run")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA, PR968_HEAD]))

    def test_workflow_run_non_matching_selector_publishes_the_run_head_only(self):
        prs = [open_main_pr(968, PR968_HEAD), open_main_pr(985, PR985_HEAD)]
        code, out = self._run(self._schedule(prs), "workflow_run",
                               GITHUB_PULL_REQUEST_NUMBERS="[7]")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA]))

    def test_workflow_run_number_list_with_null_padding_still_matches(self):
        prs = [open_main_pr(968, PR968_HEAD), open_main_pr(985, PR985_HEAD)]
        code, out = self._run(self._schedule(prs), "workflow_run",
                               GITHUB_PULL_REQUEST_NUMBERS="[968, null]")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA, PR968_HEAD]))
        code, out = self._run(self._schedule(prs), "workflow_run",
                               GITHUB_PULL_REQUEST_NUMBERS="[null]")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA, PR968_HEAD, PR985_HEAD]))

    def test_summary_write_failure_leaves_exit_code_and_stdout_untouched(self):
        prs = [open_main_pr(968, PR968_HEAD), open_main_pr(985, PR985_HEAD)]
        with tempfile.TemporaryDirectory() as scratch:
            summary = os.path.join(scratch, "missing-dir", "summary.md")
            code, out = self._run(self._schedule(prs), "workflow_run",
                                   GITHUB_PULL_REQUEST_NUMBERS="[7]",
                                   GITHUB_STEP_SUMMARY=summary)
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA]))

    def test_output_write_failure_exits_one(self):
        # The shas output is load-bearing: an I/O failure there fails the
        # run like a resolve failure (exit 1), unlike the best-effort
        # step summary above.
        prs = [open_main_pr(968, PR968_HEAD)]
        with tempfile.TemporaryDirectory() as scratch:
            output = os.path.join(scratch, "missing-dir", "output.txt")
            code, out = self._run(self._schedule(prs), "workflow_run", output=output)
        self.assertEqual(code, 1)
        self.assertEqual(out, "")

    def test_edited_with_a_base_change_resolves_normally(self):
        pr = testlib.build_pr_record(number=985, sha=PR985_HEAD, base_ref="develop")
        transport = testlib.FakeTransport([FakeResponse(200, pr)])
        code, out = self._run(transport, "pull_request_target",
                              GITHUB_PR_ACTION="edited",
                              GITHUB_CHANGES_BASE_REF="main",
                              GITHUB_CHANGES_BASE_SHA="b" * 40)
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), [PR985_HEAD])
        self.assertEqual([call.full_url for call in transport.calls], [PR_URL])

    def test_edited_without_a_base_change_resolves_to_nothing(self):
        # A title/body edit cannot change any decision input: the guard
        # returns an empty list with no API call at all.
        transport = testlib.FakeTransport([])
        code, out = self._run(transport, "pull_request_target",
                              GITHUB_PR_ACTION="edited")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), [])
        self.assertEqual(transport.calls, [])

    def test_edited_guard_never_trips_on_other_actions(self):
        pr = testlib.build_pr_record(number=985, sha=PR985_HEAD, base_ref="develop")
        transport = testlib.FakeTransport([FakeResponse(200, pr)])
        code, out = self._run(transport, "pull_request_target",
                              GITHUB_PR_ACTION="opened")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), [PR985_HEAD])
        self.assertEqual([call.full_url for call in transport.calls], [PR_URL])

    def test_pull_request_target_emits_the_live_head_of_a_closed_retargeted_pr(self):
        pr = testlib.build_pr_record(number=985, sha=PR985_HEAD, base_ref="develop",
                                     state="closed")
        transport = testlib.FakeTransport([FakeResponse(200, pr)])
        code, out = self._run(transport, "pull_request_target", GITHUB_PR_NUMBER="985")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), [PR985_HEAD])
        self.assertEqual([call.full_url for call in transport.calls], [PR_URL])

    def test_overlapping_selectors_dedupe_to_one_entry(self):
        shared = "a" * 40
        prs = [open_main_pr(968, shared),
               open_main_pr(969, shared, head_repository="some-fork/java-profiler",
                            head_branch="patch-1")]
        code, out = self._run(self._schedule(prs), "workflow_run",
                              GITHUB_HEAD_SHA=shared,
                              GITHUB_PULL_REQUEST_NUMBERS="[968, 969]")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), [shared])

    def test_schedule_and_dispatch_emit_all_open_main_heads(self):
        prs = [open_main_pr(968, PR968_HEAD), open_main_pr(985, PR985_HEAD)]
        for event in ("schedule", "workflow_dispatch"):
            with self.subTest(event=event):
                code, out = self._run(self._schedule(prs), event)
                self.assertEqual(code, 0)
                self.assertEqual(json.loads(out), sorted([PR968_HEAD, PR985_HEAD]))

    def test_output_json_shape_via_github_output_and_stdout(self):
        with tempfile.TemporaryDirectory() as scratch:
            output = os.path.join(scratch, "out.txt")
            transport = self._schedule([open_main_pr(968, PR968_HEAD)])
            code, out = self._run(transport, "schedule", output=output)
            self.assertEqual(code, 0)
            self.assertEqual(out, "")
            with open(output, encoding="utf-8") as handle:
                written = handle.read()
        self.assertEqual(written, "shas=%s\n" % json.dumps([PR968_HEAD]))
        transport = self._schedule([open_main_pr(968, PR968_HEAD)])
        code, out = self._run(transport, "schedule")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), [PR968_HEAD])

    def test_more_than_256_shas_exit_1_without_writing_and_256_exit_0(self):
        def sha(i):
            return "a%039d" % (i,)

        for count, expected in ((256, 0), (257, 1)):
            with self.subTest(count=count):
                prs = [open_main_pr(1000 + i, sha(i)) for i in range(count)]
                with tempfile.TemporaryDirectory() as scratch:
                    output = os.path.join(scratch, "out.txt")
                    open(output, "w").close()
                    code, _ = self._run(self._schedule(prs), "schedule", output=output)
                    self.assertEqual(code, expected)
                    with open(output, encoding="utf-8") as handle:
                        written = handle.read()
                if expected == 0:
                    self.assertEqual(len(json.loads(written.split("=", 1)[1])), 256)
                else:
                    self.assertEqual(written, "")

    def test_invalid_head_sha_env_values_exit_1_before_any_request(self):
        for bad in ("1" * 39, "z" * 40, "A" * 40, PR985_HEAD.upper(),
                    "0x" + "1" * 38, ""):
            with self.subTest(bad=bad):
                transport = testlib.FakeTransport([])
                code, _ = self._run(transport, "workflow_run", GITHUB_HEAD_SHA=bad)
                self.assertEqual(code, 1)
                self.assertEqual(transport.calls, [])

    def test_invalid_pr_numbers_exit_1_before_any_request(self):
        number_cases = ["0", "-5", "abc", "9.5", None, ""]
        for bad in number_cases:
            with self.subTest(selector="pull_request_target", bad=bad):
                transport = testlib.FakeTransport([])
                code, _ = self._run(transport, "pull_request_target", GITHUB_PR_NUMBER=bad)
                self.assertEqual(code, 1)
                self.assertEqual(transport.calls, [])
        list_cases = ["[0]", '[-1]', '["968"]', "[968, 0]", "[9.5]", "968",
                     "not json", None, ""]
        for bad in list_cases:
            with self.subTest(selector="workflow_run list", bad=bad):
                transport = testlib.FakeTransport([])
                code, _ = self._run(transport, "workflow_run", GITHUB_PULL_REQUEST_NUMBERS=bad)
                self.assertEqual(code, 1)
                self.assertEqual(transport.calls, [])

    def test_unknown_event_name_or_missing_env_exits_1(self):
        missing = [
            ("push", {}),
            ("pull_request_target", {"GITHUB_PR_NUMBER": None}),
            ("workflow_run", {"GITHUB_HEAD_SHA": None}),
            ("workflow_run", {"GITHUB_HEAD_BRANCH": None}),
            ("workflow_run", {"GITHUB_HEAD_REPOSITORY": None}),
            ("workflow_run", {"GITHUB_PULL_REQUEST_NUMBERS": None}),
        ]
        for event, overrides in missing:
            with self.subTest(event=event, overrides=sorted(overrides)):
                transport = testlib.FakeTransport([])
                code, _ = self._run(transport, event, **overrides)
                self.assertEqual(code, 1)
                self.assertEqual(transport.calls, [])
        for repo in (None, "java-profiler", "DataDog/"):
            with self.subTest(repository=repo):
                code, _ = self._run(testlib.FakeTransport([]), "schedule",
                                    GITHUB_REPOSITORY=repo)
                self.assertEqual(code, 1)

    def test_api_failure_after_retries_exits_1(self):
        transport = testlib.FakeTransport([FakeResponse(500)] * 3)
        code, _ = self._run(transport, "schedule")
        self.assertEqual(code, 1)
        self.assertEqual(len(transport.calls), 3)
        transport = testlib.FakeTransport([FakeResponse(404)])
        code, _ = self._run(transport, "pull_request_target")
        self.assertEqual(code, 1)
        self.assertEqual(len(transport.calls), 1)

    def test_malformed_open_main_record_fails_closed_even_when_a_selector_matched(self):
        prs = [open_main_pr(968, PR968_HEAD), testlib.build_pr_record(number=7, sha="abc")]
        with tempfile.TemporaryDirectory() as scratch:
            output = os.path.join(scratch, "out.txt")
            open(output, "w").close()
            code, _ = self._run(self._schedule(prs), "workflow_run",
                                GITHUB_PULL_REQUEST_NUMBERS="[968]", output=output)
            self.assertEqual(code, 1)
            with open(output, encoding="utf-8") as handle:
                self.assertEqual(handle.read(), "")

    def test_malformed_fetched_pr_record_exits_1(self):
        pr = testlib.build_pr_record(number=985, sha=PR985_HEAD.upper())
        transport = testlib.FakeTransport([FakeResponse(200, pr)])
        code, _ = self._run(transport, "pull_request_target", GITHUB_PR_NUMBER="985")
        self.assertEqual(code, 1)

    def test_head_repository_and_branch_values_reach_only_comparisons(self):
        prs = [open_main_pr(968, PR968_HEAD)]
        transport = self._schedule(prs)
        code, out = self._run(transport, "workflow_run",
                              GITHUB_HEAD_REPOSITORY="evil/repo; rm -rf /",
                              GITHUB_HEAD_BRANCH="$(touch pwned)",
                              GITHUB_PULL_REQUEST_NUMBERS="[968]")
        self.assertEqual(code, 0)
        self.assertEqual(json.loads(out), sorted([SHA, PR968_HEAD]))
        self.assertEqual([call.full_url for call in transport.calls], [PULLS_URL])


class ResolveEnvOnlyContractTest(unittest.TestCase):
    """The resolver executes nothing: the gate module carries no command
    execution surface."""

    def test_module_source_has_no_command_execution_surface(self):
        with open(gate.__file__, encoding="utf-8") as handle:
            source = handle.read()
        self.assertNotIn("subprocess", source)
        self.assertNotIn("os.system", source)


if __name__ == "__main__":
    unittest.main()
