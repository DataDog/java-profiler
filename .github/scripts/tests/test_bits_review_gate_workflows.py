# Copyright 2026, Datadog, Inc.
"""Static contract tests for the Bits review gate workflow files.

Pure stdlib text assertions over the receiver workflow: exact triggers,
empty top-level permissions with none in the job, no actions or checkout,
no expressions in ``run:`` blocks, ``timeout-minutes``, and no artifacts,
secrets or tokens. Publisher assertions extend this module: exact
triggers, trusted main checkout, SHA-pinned actions, per-job permission
sets, per-SHA concurrency without cancel, env-only inputs and the
explicit ``$SHA`` publish target. Policy assertions parse the publisher
Octo-STS file: exact issuer, subject and event claims, the protected
main ref, the workflow-ref pin and ``statuses: write`` only. Wiring
assertions extend this module as well: the ``ci.yml`` ``script-tests``
loop runs the gate runner additively, the runner's unittest discover
pattern selects only this gate's family (an unrelated module is not
selected) while the shared helper stays importable, and AGENTS.md's
Work Tracking pointer names the workflow, the ``bits-review/head``
context and the design doc without an activation claim. No YAML
dependency; every assertion fails when its element is removed or
mistyped.
"""

from fnmatch import fnmatch
import os
import re
import unittest

REPO_ROOT = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "..")
)
RECEIVER_WORKFLOW = os.path.join(
    REPO_ROOT, ".github", "workflows", "bits-review-event.yml"
)
PUBLISHER_WORKFLOW = os.path.join(
    REPO_ROOT, ".github", "workflows", "bits-review-gate.yml"
)
CHECKOUT_PIN = "actions/checkout@3d3c42e5aac5ba805825da76410c181273ba90b1 # v7.0.1"
OCTO_STS_PIN = "DataDog/dd-octo-sts-action@c85802a58e202b7e764b5441e4378c76043c8108 # v1.0.5"
POLICY_FILE = os.path.join(
    REPO_ROOT,
    ".github",
    "chainguard",
    "self.bits-review-gate.publish-status.sts.yaml",
)
POLICY_ISSUER = "https://token.actions.githubusercontent.com"
POLICY_SUBJECT_PATTERN = (
    "repo:DataDog/java-profiler:(pull_request|ref:refs/heads/main)"
)
POLICY_EVENT_NAMES = {
    "pull_request_target",
    "workflow_run",
    "schedule",
    "workflow_dispatch",
}
POLICY_JOB_WORKFLOW_REF = (
    r"DataDog/java-profiler/\.github/workflows/bits-review-gate\.yml"
    r"@refs/heads/main"
)
CI_WORKFLOW = os.path.join(REPO_ROOT, ".github", "workflows", "ci.yml")
GATE_RUNNER = ".github/scripts/tests/test_bits_review_gate.sh"
TICKET_RUNNER = ".github/scripts/tests/test_check_pr_ticket.sh"
RUNNER_SCRIPT = os.path.join(REPO_ROOT, *GATE_RUNNER.split("/"))
TESTS_DIR = os.path.dirname(RUNNER_SCRIPT)
AGENTS_FILE = os.path.join(REPO_ROOT, "AGENTS.md")
DISCOVER_PATTERN = "test_bits_review_gate_*.py"
FAMILY_MODULES = {
    "test_bits_review_gate_api.py",
    "test_bits_review_gate_policy.py",
    "test_bits_review_gate_publish.py",
    "test_bits_review_gate_workflows.py",
}
HELPER_MODULE = "bits_review_gate_testlib.py"
# Activation-claim words the AGENTS.md pointer must not use: the check is
# designed, not required, until separately approved activation lands.
POINTER_CLAIM = re.compile(
    r"(?i)\b(requir(e|es|ed)|enforce[ds]?|enforcement"
    r"|blocks?|blocking|must)\b"
)


def read_text(path):
    with open(path, "r", encoding="utf-8") as handle:
        return handle.read()


def block_after(text, key):
    """The indented block that follows a top-level ``key:`` line."""
    match = re.search(r"^%s:\n(.*?)(?=^\S|\Z)" % re.escape(key), text, re.M | re.S)
    return match.group(1) if match else ""


def trigger_types(text, trigger):
    """The exact ``types`` list of ``trigger``, or None when absent."""
    match = re.search(
        r"^  %s:\n    types: \[([^\]]*)\]" % re.escape(trigger), text, re.M
    )
    if match is None:
        return None
    return [item.strip() for item in match.group(1).split(",")]


def run_blocks(text):
    """Every ``run:`` value: the key line's remainder plus deeper-indented lines."""
    lines = text.splitlines()
    blocks = []
    index = 0
    while index < len(lines):
        match = re.match(r"^(\s*)run:(.*)$", lines[index])
        if match is None:
            index += 1
            continue
        indent, rest = match.group(1), match.group(2).strip()
        block = [rest]
        index += 1
        while index < len(lines):
            if lines[index].strip() == "":
                index += 1
                continue
            deeper = re.match(r"^(\s*)\S", lines[index])
            if deeper is not None and len(deeper.group(1)) > len(indent):
                block.append(lines[index].strip())
                index += 1
            else:
                break
        blocks.append("\n".join(block))
    return blocks


def sub_block(text, key):
    """The child block of one 2-space-indented ``key:`` (a trigger or job).

    Ends at the next 2-space key or the end of the parent block.
    """
    match = re.search(
        r"^  %s:\n(.*?)(?=^  \S|\Z)" % re.escape(key), text, re.M | re.S
    )
    return match.group(1) if match else ""


def job_block(jobs, job):
    """The body of one job inside the ``jobs:`` block."""
    return sub_block(jobs, job)


def job_permissions(block):
    """The permissions mapping of a job block, or None when absent."""
    match = re.search(
        r"^    permissions:\n((?:      [^\n]*\n)+)", block, re.M
    )
    if match is None:
        return None
    entries = {}
    for line in match.group(1).splitlines():
        key, _, value = line.strip().partition(": ")
        entries[key] = value
    return entries


def exact_line(block, line):
    """Whether ``line`` appears as a full line, ignoring indentation."""
    return re.search(r"^[ \t]*%s$" % re.escape(line), block, re.M) is not None


class ReceiverWorkflowTest(unittest.TestCase):
    """The no-op permissionless receiver: bits-review-event.yml."""

    @classmethod
    def setUpClass(cls):
        cls.text = read_text(RECEIVER_WORKFLOW)

    def test_workflow_name(self):
        self.assertIsNotNone(
            re.search(r"^name: Bits review event$", self.text, re.M)
        )

    def test_triggers_are_exactly_the_two_events(self):
        on_keys = set(re.findall(r"^  ([^\s:]+):", block_after(self.text, "on"), re.M))
        self.assertEqual(on_keys, {"pull_request_review", "pull_request"})

    def test_review_trigger_types_exact(self):
        self.assertEqual(
            trigger_types(self.text, "pull_request_review"),
            ["submitted", "edited", "dismissed"],
        )

    def test_pr_trigger_types_exact(self):
        self.assertEqual(trigger_types(self.text, "pull_request"), ["edited"])

    def test_top_level_permissions_empty(self):
        self.assertEqual(
            re.findall(r"^permissions:.*$", self.text, re.M), ["permissions: {}"]
        )

    def test_job_has_no_permissions(self):
        self.assertEqual(re.findall(r"^[ \t]+permissions:", self.text, re.M), [])

    def test_no_actions_and_no_checkout(self):
        self.assertNotIn("uses:", self.text)
        self.assertNotIn("checkout", self.text.lower())

    def test_exactly_one_static_echo_run_step(self):
        blocks = run_blocks(self.text)
        self.assertEqual(len(blocks), 1)
        self.assertTrue(blocks[0].startswith("echo "), blocks[0])

    def test_run_blocks_have_no_expressions(self):
        for block in run_blocks(self.text):
            self.assertNotIn("${{", block)

    def test_timeout_minutes_present(self):
        self.assertIsNotNone(
            re.search(r"^[ \t]+timeout-minutes: \d+$", self.text, re.M)
        )

    def test_exactly_one_job(self):
        jobs = re.findall(r"^  ([^\s:]+):", block_after(self.text, "jobs"), re.M)
        self.assertEqual(len(jobs), 1)

    def test_no_secrets_or_token_references(self):
        self.assertIsNone(re.search(r"(?i)token|secret", self.text))

    def test_no_artifacts(self):
        self.assertIsNone(re.search(r"(?i)artifact", self.text))


class PublisherWorkflowTest(unittest.TestCase):
    """The trusted main-branch publisher: bits-review-gate.yml."""

    @classmethod
    def setUpClass(cls):
        cls.text = read_text(PUBLISHER_WORKFLOW)
        cls.on = block_after(cls.text, "on")
        cls.jobs = block_after(cls.text, "jobs")
        cls.resolve = job_block(cls.jobs, "resolve")
        cls.publish = job_block(cls.jobs, "publish")

    def test_workflow_name(self):
        self.assertIsNotNone(
            re.search(r"^name: Bits review gate$", self.text, re.M)
        )

    def test_both_jobs_carry_a_timeout(self):
        # Without a timeout the jobs inherit the 360-minute default, and
        # _fetch can sleep up to 300 s per retry — a stalled publish also
        # holds its per-SHA concurrency group (cancel-in-progress false).
        for block, name in ((self.resolve, "resolve"), (self.publish, "publish")):
            with self.subTest(job=name):
                self.assertIsNotNone(
                    re.search(r"^[ \t]+timeout-minutes: \d+$", block, re.M))

    def test_triggers_are_exactly_the_four_events(self):
        on_keys = set(re.findall(r"^  ([^\s:]+):", self.on, re.M))
        self.assertEqual(
            on_keys,
            {"pull_request_target", "workflow_run", "schedule", "workflow_dispatch"},
        )

    def test_pull_request_target_types_exact_and_unfiltered(self):
        self.assertEqual(
            trigger_types(self.text, "pull_request_target"),
            ["opened", "reopened", "synchronize", "edited", "closed"],
        )
        # A branch filter would scope the event before the resolver can.
        self.assertEqual(
            sub_block(self.on, "pull_request_target").split(),
            ["types:", "[opened,", "reopened,", "synchronize,", "edited,",
             "closed]"],
        )

    def test_workflow_run_names_receiver_exactly(self):
        block = sub_block(self.on, "workflow_run")
        self.assertTrue(
            exact_line(block, 'workflows: ["Bits review event"]'), block
        )
        self.assertTrue(exact_line(block, "types: [completed]"), block)

    def test_schedule_cron_exact(self):
        self.assertTrue(
            exact_line(sub_block(self.on, "schedule"), "- cron: '*/30 * * * *'")
        )

    def test_workflow_dispatch_has_no_inputs(self):
        self.assertEqual(sub_block(self.on, "workflow_dispatch").strip(), "")

    def test_top_level_permissions_empty(self):
        self.assertEqual(
            re.findall(r"^permissions:.*$", self.text, re.M), ["permissions: {}"]
        )

    def test_exactly_two_jobs(self):
        jobs = re.findall(r"^  ([^\s:]+):", self.jobs, re.M)
        self.assertEqual(jobs, ["resolve", "publish"])

    def test_resolve_guard_is_exact(self):
        self.assertTrue(
            exact_line(self.resolve, "if: github.ref == 'refs/heads/main'")
        )

    def test_resolve_guard_rationale_is_pinned(self):
        # pull_request_target presents the base-branch ref, so the main-ref
        # guard is live for PR events too; pin the rationale comment text.
        self.assertIn(
            "pull_request_target sets github.ref to the base branch",
            self.resolve,
        )
        self.assertTrue(
            exact_line(self.resolve, "if: github.ref == 'refs/heads/main'")
        )

    def test_resolve_permissions_exact(self):
        self.assertEqual(
            job_permissions(self.resolve),
            {"contents": "read", "pull-requests": "read"},
        )

    def test_trusted_main_checkout_in_both_jobs(self):
        for block in (self.resolve, self.publish):
            self.assertTrue(exact_line(block, "uses: " + CHECKOUT_PIN), block)
            self.assertTrue(exact_line(block, "ref: refs/heads/main"), block)
            self.assertTrue(
                exact_line(block, "persist-credentials: false"), block
            )
        refs = re.findall(r"^ +ref: (.+)$", self.text, re.M)
        self.assertEqual(refs, ["refs/heads/main", "refs/heads/main"])
        self.assertEqual(
            len(re.findall(r"^ *uses: actions/checkout@", self.text, re.M)), 2
        )

    def test_no_pr_head_checkout(self):
        for banned in (
            "github.head_ref",
            "github.event.pull_request.head",
            "github.ref_name",
        ):
            self.assertNotIn(banned, self.text)

    def test_all_uses_lines_sha_pinned_with_version_comment(self):
        pins = re.findall(r"^ *uses: (.+)$", self.text, re.M)
        self.assertTrue(pins)
        for pin in pins:
            self.assertRegex(pin, r"^[^@\s]+@[0-9a-f]{40} # v[^\s]+$")

    def test_octo_sts_action_pinned_and_scoped(self):
        self.assertTrue(
            exact_line(self.publish, "uses: " + OCTO_STS_PIN), self.publish
        )
        self.assertTrue(
            exact_line(self.publish, "scope: DataDog/java-profiler"), self.publish
        )
        self.assertTrue(
            exact_line(
                self.publish, "policy: self.bits-review-gate.publish-status"
            ),
            self.publish,
        )

    def test_resolve_inputs_arrive_through_env_only(self):
        env_lines = (
            "GITHUB_TOKEN: ${{ github.token }}",
            "GITHUB_PR_NUMBER: ${{ github.event.pull_request.number }}",
            "GITHUB_HEAD_SHA: ${{ github.event.workflow_run.head_sha }}",
            "GITHUB_HEAD_REPOSITORY: "
            "${{ github.event.workflow_run.head_repository.full_name }}",
            "GITHUB_HEAD_BRANCH: ${{ github.event.workflow_run.head_branch }}",
            "GITHUB_PULL_REQUEST_NUMBERS: "
            "${{ toJSON(github.event.workflow_run.pull_requests[*].number) }}",
            "GITHUB_PR_ACTION: ${{ github.event.action }}",
            "GITHUB_CHANGES_BASE_REF: ${{ github.event.changes.base.ref.from }}",
            "GITHUB_CHANGES_BASE_SHA: ${{ github.event.changes.base.sha.from }}",
        )
        for line in env_lines:
            self.assertTrue(exact_line(self.resolve, line), line)

    def test_resolve_run_command_exact(self):
        self.assertEqual(
            run_blocks(self.resolve),
            ["python3 .github/scripts/bits_review_gate.py resolve"],
        )

    def test_resolve_step_output_exposed_as_job_output(self):
        self.assertTrue(exact_line(self.resolve, "id: resolve"), self.resolve)
        self.assertTrue(
            exact_line(
                self.resolve, "shas: ${{ steps.resolve.outputs.shas }}"
            ),
            self.resolve,
        )

    def test_publish_needs_and_guard(self):
        self.assertTrue(exact_line(self.publish, "needs: resolve"), self.publish)
        self.assertTrue(
            exact_line(
                self.publish,
                "if: github.ref == 'refs/heads/main' "
                "&& needs.resolve.outputs.shas != '[]'",
            ),
            self.publish,
        )

    def test_publish_permissions_exact(self):
        self.assertEqual(
            job_permissions(self.publish),
            {
                "contents": "read",
                "pull-requests": "read",
                "statuses": "read",
                "id-token": "write",
            },
        )

    def test_matrix_sha_from_resolver_output(self):
        self.assertTrue(
            exact_line(
                self.publish,
                "sha: ${{ fromJSON(needs.resolve.outputs.shas) }}",
            ),
            self.publish,
        )
        self.assertTrue(
            exact_line(self.publish, "fail-fast: false"), self.publish
        )

    def test_per_sha_concurrency_without_cancel(self):
        self.assertTrue(
            exact_line(
                self.publish, "group: bits-review-gate-${{ matrix.sha }}"
            ),
            self.publish,
        )
        self.assertTrue(
            exact_line(self.publish, "cancel-in-progress: false"), self.publish
        )

    def test_no_environment_key(self):
        self.assertIsNone(re.search(r"^[ \t]+environment:", self.text, re.M))

    def test_run_blocks_have_no_expressions(self):
        for block in run_blocks(self.text):
            self.assertNotIn("${{", block)

    def test_publish_targets_explicit_matrix_sha(self):
        self.assertEqual(
            run_blocks(self.publish),
            ['python3 .github/scripts/bits_review_gate.py publish --sha "$SHA"'],
        )
        for line in (
            "SHA: ${{ matrix.sha }}",
            "GITHUB_TOKEN: ${{ github.token }}",
            "STATUS_TOKEN: ${{ steps.octo-sts.outputs.token }}",
        ):
            self.assertTrue(exact_line(self.publish, line), line)
        self.assertNotIn("GITHUB_SHA", self.text)
        self.assertNotIn("github.sha", self.text)

    def test_no_artifacts(self):
        self.assertNotIn("artifact", self.text.lower())


class PublisherOctoStsPolicyTest(unittest.TestCase):
    """The status-write-only publisher policy: the Octo-STS claim pins."""

    @classmethod
    def setUpClass(cls):
        cls.text = read_text(POLICY_FILE)

    def top_level_value(self, key):
        """The single ``key:`` value at the top level, or None when absent."""
        values = re.findall(r"^%s: (.+)$" % re.escape(key), self.text, re.M)
        return values[0] if values else None

    def claim_value(self, claim):
        """The value of one ``claim_pattern`` entry, or None when absent."""
        values = re.findall(r"^  %s: (.+)$" % re.escape(claim), self.text, re.M)
        return values[0] if values else None

    def test_issuer_is_github_actions_oidc(self):
        self.assertEqual(self.top_level_value("issuer"), POLICY_ISSUER)

    def test_subject_pattern_covers_exactly_both_forms(self):
        self.assertEqual(
            self.top_level_value("subject_pattern"), POLICY_SUBJECT_PATTERN
        )
        forms = re.findall(
            r"^subject_pattern: repo:DataDog/java-profiler:\(([^)]*)\)$",
            self.text,
            re.M,
        )
        self.assertEqual(len(forms), 1)
        self.assertEqual(forms[0].split("|"), ["pull_request", "ref:refs/heads/main"])

    def test_event_names_are_exactly_the_four(self):
        events = re.findall(
            r"^  event_name: \(([^)]*)\)$", self.text, re.M
        )
        self.assertEqual(len(events), 1)
        self.assertEqual(set(events[0].split("|")), POLICY_EVENT_NAMES)

    def test_ref_is_protected_main(self):
        self.assertEqual(self.claim_value("ref"), "refs/heads/main")
        self.assertEqual(self.claim_value("ref_protected"), '"true"')

    def test_job_workflow_ref_pinned_to_gate_on_main(self):
        self.assertEqual(
            self.claim_value("job_workflow_ref"), POLICY_JOB_WORKFLOW_REF
        )

    def test_permissions_are_statuses_write_only(self):
        block = re.search(
            r"^permissions:\n((?:  [^\n]+\n)+)", self.text, re.M
        )
        self.assertIsNotNone(block, self.text)
        entries = {}
        for line in block.group(1).splitlines():
            key, _, value = line.strip().partition(": ")
            entries[key] = value
        self.assertEqual(entries, {"statuses": "write"})


class CiScriptTestsWiringTest(unittest.TestCase):
    """The additive script-tests loop entry for the gate runner in ci.yml."""

    @classmethod
    def setUpClass(cls):
        cls.jobs = block_after(read_text(CI_WORKFLOW), "jobs")
        cls.job = sub_block(cls.jobs, "script-tests")

    def loop_entries(self):
        """The whitespace-separated paths of the job's ``for t in`` loop."""
        match = re.search(r"^ +for t in (.+); do$", self.job, re.M)
        self.assertIsNotNone(match, self.job)
        return match.group(1).split()

    def test_script_tests_job_exists(self):
        self.assertNotEqual(self.job, "")

    def test_loop_runs_gate_runner(self):
        self.assertIn(GATE_RUNNER, self.loop_entries())

    def test_loop_keeps_existing_entries(self):
        # Additive only: the PR-ticket runner and the utils glob stay.
        entries = self.loop_entries()
        self.assertIn("utils/tests/*.sh", entries)
        self.assertIn(TICKET_RUNNER, entries)


class RunnerDiscoveryTest(unittest.TestCase):
    """The gate runner discovers only this gate's test family (INV-22);
    the design doc's AC12 is the Octo-STS claim-denial test drive, not
    this local runner contract."""

    @classmethod
    def setUpClass(cls):
        cls.text = read_text(RUNNER_SCRIPT)

    def discover_pattern(self):
        """The single ``-p`` pattern of the runner's discover command."""
        patterns = re.findall(r"-p '([^']+)'", self.text)
        self.assertEqual(len(patterns), 1, patterns)
        return patterns[0]

    def test_pattern_is_exactly_the_gate_family(self):
        self.assertEqual(self.discover_pattern(), DISCOVER_PATTERN)

    def test_pattern_selects_only_the_family_modules_present(self):
        pattern = self.discover_pattern()
        matched = {
            name for name in os.listdir(TESTS_DIR) if fnmatch(name, pattern)
        }
        self.assertEqual(matched, FAMILY_MODULES)

    def test_pattern_selects_no_unrelated_module(self):
        pattern = self.discover_pattern()
        for name in (
            "test_other.py",
            "test_check_pr_ticket.py",
            "test_quarantine.py",
            HELPER_MODULE,
            "run_release_cli.py",
            GATE_RUNNER.split("/")[-1],
        ):
            self.assertFalse(fnmatch(name, pattern), name)

    def test_helper_import_stays_legal(self):
        # The helper is never discovered as a suite, but family modules
        # import it, so discovery of the family depends on it existing.
        self.assertTrue(
            os.path.isfile(os.path.join(TESTS_DIR, HELPER_MODULE)), HELPER_MODULE
        )
        importers = [
            name
            for name in sorted(FAMILY_MODULES)
            if "bits_review_gate_testlib" in read_text(
                os.path.join(TESTS_DIR, name)
            )
        ]
        self.assertTrue(importers, "no family module imports the helper")


class AgentsWorkTrackingPointerTest(unittest.TestCase):
    """The concise Work Tracking pointer to the bits review gate design."""

    @classmethod
    def setUpClass(cls):
        cls.text = read_text(AGENTS_FILE)
        match = re.search(
            r"^## Work Tracking\n(.*?)(?=^## |\Z)", cls.text, re.M | re.S
        )
        cls.section = match.group(1) if match else ""

    def pointer_paragraph(self):
        """The wrapped paragraph of the pointer, joined onto one line."""
        lines = self.section.splitlines()
        starts = [i for i, line in enumerate(lines) if "bits-review-gate" in line]
        self.assertEqual(len(starts), 1, starts)
        paragraph = [lines[starts[0]]]
        for line in lines[starts[0] + 1 :]:
            if not line.strip():
                break
            paragraph.append(line)
        return " ".join(paragraph)

    def test_pointer_follows_the_pr_ticket_sentence(self):
        ticket = self.section.find(".github/workflows/pr-ticket.yml")
        self.assertNotEqual(ticket, -1)
        self.assertGreater(self.section.find("bits-review-gate"), ticket)

    def test_pointer_names_workflow_context_and_design_doc(self):
        paragraph = self.pointer_paragraph()
        for token in (
            "bits-review-gate",
            "bits-review/head",
            "doc/BitsReviewMergeGateDesign.md",
        ):
            self.assertIn(token, paragraph)

    def test_pointer_makes_no_activation_claim(self):
        paragraph = self.pointer_paragraph()
        self.assertIsNone(POINTER_CLAIM.search(paragraph), paragraph)

    def test_pointer_is_the_only_gate_mention_in_agents_md(self):
        self.assertEqual(self.text.count("bits-review-gate"), 1)


if __name__ == "__main__":
    unittest.main()
