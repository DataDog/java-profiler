# Copyright 2026, Datadog, Inc.
"""Contracts between certification, its status waiter, and offline CI tests."""

from pathlib import Path
import re
import unittest


ROOT = Path(__file__).resolve().parents[3]


def job(text, name):
    """Read a job's indented block without requiring a YAML dependency."""
    match = re.search(r"^  " + re.escape(name) + r":\n(.*?)(?=^  \S|\Z)",
                      text, re.MULTILINE | re.DOTALL)
    if match is None:
        raise AssertionError("Missing job " + name)
    return match.group(1)


class CertificationWorkflowTest(unittest.TestCase):
    def setUp(self):
        self.workflow = (ROOT / ".github/workflows/certification.yml").read_text()
        self.integration = job(self.workflow, "gitlab-integration")

    def test_no_gitlab_credentials_or_direct_api_access(self):
        for removed in ("GITLAB_API_TOKEN", "GITLAB_TOKEN", "PRIVATE-TOKEN",
                        "gitlab.ddbuild.io", "INTEGRATION_JOBS"):
            with self.subTest(removed=removed):
                self.assertNotIn(removed, self.workflow)

    def test_waiter_has_candidate_checkout_and_read_only_permissions(self):
        self.assertIn("if: github.ref == 'refs/heads/main'", self.integration)
        self.assertIn("timeout-minutes: 420", self.integration)
        self.assertRegex(self.integration, r"uses: actions/checkout@[0-9a-f]{40}")
        self.assertIn("ref: ${{ github.sha }}", self.integration)
        self.assertIn("persist-credentials: false", self.integration)
        self.assertRegex(self.integration,
                         r"permissions:\n      contents: read\n      statuses: read\n")
        self.assertIn("GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}", self.integration)
        self.assertIn("run: python3 .github/scripts/wait_for_integration.py",
                      self.integration)
        self.assertNotIn("write", self.integration)

    def test_certification_and_failure_report_still_depend_on_integration(self):
        for name in ("certify", "report-failure"):
            self.assertIn("needs: [test-debug, test-asan, slow-test-debug, "
                          "slow-test-asan, fuzz, gitlab-integration", job(self.workflow, name))
        self.assertIn('--suite "testDebug+testAsan (regular+slow, gtests), fuzz, '
                      'dd-trace-integration"', job(self.workflow, "certify"))
        self.assertIn("for job in test-debug test-asan slow-test-debug slow-test-asan "
                      "fuzz gitlab-integration certify; do",
                      job(self.workflow, "report-failure"))

    def test_offline_ci_runs_certification_test_family(self):
        ci = (ROOT / ".github/workflows/ci.yml").read_text()
        self.assertIn("python3 -m unittest discover -s .github/scripts/tests "
                      "-p 'test_certification_*.py'", job(ci, "release-automation-tests"))


if __name__ == "__main__":
    unittest.main()
