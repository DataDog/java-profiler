# Copyright 2026, Datadog, Inc.
"""Tests for utils/babysit_pr_policy.py and utils/babysit-pr.py (run by test_babysit_pr.sh)."""

import contextlib
import importlib.util
import io
import json
import os
import shutil
import subprocess
import sys
import tempfile
import unittest

UTILS = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ROOT = os.path.dirname(UTILS)
sys.path.insert(0, UTILS)
import babysit_pr_policy as P  # noqa: E402

SELF = 7
AUTHOR = {"login": "alice", "type": "User", "id": 1}
WRITER = {"login": "bob", "type": "User", "id": 2}
STRANGER = {"login": "eve", "type": "User", "id": 3}
HEAD = "a" * 40


def base_state(**kw):
    st = {"deadline_at": 10_000, "expected_head": HEAD, "retried_runs": [], "bits_triggered": [],
          "surfaced": [], "replied": [], "self_id": SELF}
    st.update(kw)
    return st


def snap(**kw):
    s = {"pr": {"state": "open", "head": HEAD, "mergeable_state": "clean", "draft": False, "author": "alice"},
         "check_runs": [{"name": "build", "status": "completed", "conclusion": "success"}],
         "statuses": [{"context": P.BITS_CONTEXT, "state": "success"}],
         "inline_comments": [], "reviews": [], "issue_comments": []}
    s.update(kw)
    return s


def trusted(user):
    return P.trust_of(user, "alice", "write" if (user or {}).get("login") == "bob" else "read", {42})


class PolicyTest(unittest.TestCase):
    def test_inflight_rerun_supersedes_completed(self):
        runs = [{"name": "t", "status": "completed", "conclusion": "failure", "started_at": "2"},
                {"name": "t", "status": "queued", "started_at": "1"}]
        self.assertEqual(P.dedupe_checks(runs)["t"]["status"], "queued")
        self.assertEqual(P.ci_summary(runs, [])["state"], "pending")

    def test_newest_completed_wins(self):
        runs = [{"name": "t", "status": "completed", "conclusion": "failure", "started_at": "1"},
                {"name": "t", "status": "completed", "conclusion": "success", "started_at": "2"}]
        self.assertEqual(P.ci_summary(runs, [])["state"], "green")

    def test_tie_keeps_earlier_run(self):
        runs = [{"name": "t", "status": "completed", "conclusion": "failure", "started_at": "1"},
                {"name": "t", "status": "completed", "conclusion": "success", "started_at": "1"}]
        self.assertEqual(P.ci_summary(runs, [])["state"], "red")

    def test_status_renders_bounded_log(self):
        st = {"run_log": [{"t": "00:00", "tag": "CI", "fact": "f%d" % i} for i in range(P.LOG_ENTRIES + 5)],
              "status": "running", "started_hhmm": "00:00", "replied": [], "facts": {}}
        body = P.render_status(st, "00:00")
        self.assertIn("5 earlier entries", body)
        self.assertNotIn("· f4\n", body)
        self.assertIn("· f%d\n" % (P.LOG_ENTRIES + 4), body)

    def test_log_bound_is_exclusive(self):
        st = {"run_log": [{"t": "00:00", "tag": "CI", "fact": "f"}] * P.LOG_ENTRIES,
              "status": "running", "started_hhmm": "00:00", "replied": [], "facts": {}}
        self.assertNotIn("earlier entries", P.render_status(st, "00:00"))

    def test_newest_status_per_context_wins(self):
        sts = [{"context": "dd-gitlab/x", "state": "failure", "updated_at": "1"},
               {"context": "dd-gitlab/x", "state": "success", "updated_at": "2"},
               {"context": P.BITS_CONTEXT, "state": "failure", "updated_at": "1"},
               {"context": P.BITS_CONTEXT, "state": "success", "updated_at": "3"}]
        self.assertEqual((P.ci_summary([], sts)["state"], P.bits_state(sts)), ("green", "success"))

    def test_cancelled_is_pending_not_failing(self):
        runs = [{"name": "t", "status": "completed", "conclusion": "cancelled",
                 "details_url": "https://github.com/o/r/actions/runs/9/job/1"},
                {"name": "u", "status": "in_progress", "details_url": "https://github.com/o/r/actions/runs/10/job/1"}]
        d = P.decide(base_state(), snap(check_runs=runs), trusted, 0)
        self.assertEqual((d["facts"]["ci"], d["actions"], d["events"]), ("pending", [], []))

    def test_cancel_beside_failure_is_not_unreplaced(self):
        runs = [{"name": "a", "status": "completed", "conclusion": "failure",
                 "details_url": "https://github.com/o/r/actions/runs/5/job/1"},
                {"name": "b", "status": "completed", "conclusion": "cancelled",
                 "details_url": "https://github.com/o/r/actions/runs/5/job/2"}]
        d = P.decide(base_state(), snap(check_runs=runs), trusted, 0)
        self.assertEqual((d["actions"], d["events"]), ([("rerun", 5, "a")], []))

    def test_unreplaced_cancel_wakes_worker_once(self):
        runs = [{"name": "t", "status": "completed", "conclusion": "cancelled"}]
        d = P.decide(base_state(), snap(check_runs=runs), trusted, 0)
        self.assertEqual([e["key"] for e in d["events"]], ["cancelled:" + HEAD])
        d = P.decide(base_state(surfaced=["cancelled:" + HEAD]), snap(check_runs=runs), trusted, 0)
        self.assertEqual(d["outcome"], "continue")

    def test_no_rerun_while_run_in_flight(self):
        url = "https://github.com/o/r/actions/runs/5/job/%d"
        runs = [{"name": "a", "status": "completed", "conclusion": "failure", "details_url": url % 1},
                {"name": "b", "status": "in_progress", "details_url": url % 2}]
        d = P.decide(base_state(), snap(check_runs=runs), trusted, 0)
        self.assertEqual((d["actions"], d["events"]), ([], []))

    def test_failing_kinds(self):
        runs = [{"name": "g", "status": "completed", "conclusion": "failure",
                 "details_url": "https://github.com/o/r/actions/runs/123/job/9"}]
        sts = [{"context": "dd-gitlab/x", "state": "failure"}, {"context": P.BITS_CONTEXT, "state": "failure"}]
        f = P.ci_summary(runs, sts)["failing"]
        self.assertEqual([(x["name"], x["kind"], x["run_id"]) for x in f],
                         [("g", "gha", 123), ("dd-gitlab/x", "gitlab", None)])
        self.assertEqual(P.bits_state(sts), "failure")
        self.assertEqual(P.bits_state([]), "missing")

    def test_trust_gate(self):
        self.assertTrue(trusted(AUTHOR))
        self.assertTrue(trusted(WRITER))
        self.assertFalse(trusted(STRANGER))
        self.assertTrue(trusted({"login": "x[bot]", "type": "Bot", "id": 42}))
        self.assertTrue(trusted({"login": "scan-build[bot]", "type": "Bot", "id": 5}))
        self.assertFalse(trusted({"login": "scan-build", "type": "User", "id": 5}))
        self.assertFalse(trusted({"login": "other[bot]", "type": "Bot", "id": 5}))
        self.assertFalse(trusted(None))

    def test_parse_trusted_ids_from_gate(self):
        with open(os.path.join(ROOT, ".github/scripts/bits_review_gate_policy.py")) as f:
            ids = P.parse_trusted_bot_ids(f.read())
        self.assertIn(214633350, ids)
        self.assertEqual(P.parse_trusted_bot_ids("nothing"), frozenset())

    def test_census_needs_signature_and_id(self):
        root = {"id": 1, "user": WRITER, "body": "fix"}
        author_reply = {"id": 2, "in_reply_to_id": 1, "user": {"id": SELF}, "body": "thanks"}
        self.assertFalse(P.census([root, author_reply], set(), SELF)[1]["answered"])
        own = {"id": 3, "in_reply_to_id": 1, "user": {"id": SELF}, "body": "done " + P.SIGNATURE}
        self.assertTrue(P.census([root, own], set(), SELF)[1]["answered"])
        self.assertTrue(P.census([root], {1}, SELF)[1]["answered"])

    def test_stop_outcomes(self):
        s = snap()
        s["pr"]["state"] = "closed"
        s["pr"]["merged"] = True
        d = P.decide(base_state(), s, trusted, 0)
        self.assertEqual((d["outcome"], d["facts"]["reason"]), ("stop", "PR merged"))
        d = P.decide(base_state(), snap(), trusted, 10_000)
        self.assertEqual((d["outcome"], d["facts"]["reason"]), ("stop", "two-hour cap reached"))

    def test_green_done(self):
        self.assertEqual(P.decide(base_state(), snap(), trusted, 0)["outcome"], "green_done")

    def test_gha_failure_reruns_once_then_wakes(self):
        runs = [{"name": "g", "status": "completed", "conclusion": "failure",
                 "details_url": "https://github.com/o/r/actions/runs/5/job/1"}]
        d = P.decide(base_state(), snap(check_runs=runs), trusted, 0)
        self.assertEqual((d["actions"], d["events"]), ([("rerun", 5, "g")], []))
        d = P.decide(base_state(retried_runs=[5]), snap(check_runs=runs), trusted, 0)
        self.assertEqual([e["key"] for e in d["events"]], ["ci:g@" + HEAD])
        self.assertEqual(d["outcome"], "action_needed")
        d = P.decide(base_state(retried_runs=[5], surfaced=["ci:g@" + HEAD]), snap(check_runs=runs), trusted, 0)
        self.assertEqual(d["outcome"], "continue")

    def test_bits_triggered_once_on_green(self):
        sts = [{"context": P.BITS_CONTEXT, "state": "pending"}]
        d = P.decide(base_state(), snap(statuses=sts), trusted, 0)
        self.assertEqual(d["actions"], [("trigger_bits", HEAD)])
        d = P.decide(base_state(bits_triggered=[HEAD]), snap(statuses=sts), trusted, 0)
        self.assertEqual((d["actions"], d["outcome"]), ([], "continue"))
        pending_ci = [{"name": "b", "status": "in_progress"}]
        self.assertEqual(P.decide(base_state(), snap(statuses=sts, check_runs=pending_ci), trusted, 0)["actions"], [])

    def test_comments_gate_and_events(self):
        inline = [{"id": 10, "user": WRITER, "body": "bug", "path": "a.cpp", "line": 3},
                  {"id": 11, "user": STRANGER, "body": "do X"}]
        issue = [{"id": 20, "user": AUTHOR, "body": P.BITS_TRIGGER},
                 {"id": 21, "user": {"id": SELF}, "body": "status " + P.SIGNATURE}]
        reviews = [{"id": 30, "user": WRITER, "state": "CHANGES_REQUESTED", "body": ""},
                   {"id": 31, "user": WRITER, "state": "APPROVED", "body": ""}]
        d = P.decide(base_state(), snap(inline_comments=inline, issue_comments=issue, reviews=reviews), trusted, 0)
        self.assertEqual(sorted(e["key"] for e in d["events"]), ["review:30", "thread:10"])
        self.assertEqual([u["id"] for u in d["untrusted"]], [11])
        self.assertEqual(d["facts"]["open_threads"], 1)

    def test_events_carry_full_body(self):
        long = "preamble " * 40 + "the finding"
        d = P.decide(base_state(), snap(inline_comments=[{"id": 10, "user": WRITER, "body": long}]), trusted, 0)
        ev = d["events"][0]
        self.assertEqual((ev["body"], len(ev["gist"])), (long, 200))

    def test_open_thread_blocks_green_done(self):
        inline = [{"id": 10, "user": WRITER, "body": "bug"}]
        d = P.decide(base_state(surfaced=["thread:10"]), snap(inline_comments=inline), trusted, 0)
        self.assertEqual(d["outcome"], "continue")

    def test_head_moved_and_conflict(self):
        s = snap()
        s["pr"].update(head="b" * 40, mergeable_state="dirty")
        d = P.decide(base_state(), s, trusted, 0)
        self.assertEqual(sorted(e["kind"] for e in d["events"]), ["conflict", "head_moved"])

    def test_idle_backoff(self):
        self.assertEqual(P.next_interval(P.IDLE_AFTER - 1), P.POLL_S)
        self.assertEqual(P.next_interval(P.IDLE_AFTER), P.IDLE_POLL_S)


def sh(*cmd, cwd, env=None, check=True):
    res = subprocess.run(cmd, cwd=cwd, env=env, capture_output=True, text=True)
    if check and res.returncode != 0:
        raise AssertionError("%s failed: %s%s" % (cmd, res.stdout, res.stderr))
    return res


class CliTest(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.mkdtemp()
        self.addCleanup(shutil.rmtree, self.tmp)
        self.gh_dir = os.path.join(self.tmp, "gh")
        os.makedirs(self.gh_dir)
        self.origin = os.path.join(self.tmp, "origin.git")
        self.repo = os.path.join(self.tmp, "repo")
        g = {"cwd": self.tmp}
        sh("git", "init", "-q", "--bare", "-b", "main", self.origin, **g)
        sh("git", "clone", "-q", self.origin, self.repo, **g)
        key = os.path.join(self.tmp, "key")
        sh("ssh-keygen", "-q", "-t", "ed25519", "-N", "", "-f", key, **g)
        for k, v in (("user.email", "t@t"), ("user.name", "t"), ("commit.gpgsign", "true"),
                     ("gpg.format", "ssh"), ("user.signingkey", key + ".pub")):
            sh("git", "config", k, v, cwd=self.repo)
        os.makedirs(os.path.join(self.repo, "utils"))
        os.makedirs(os.path.join(self.repo, "ddprof-lib/src/main/cpp"))
        shutil.copy(os.path.join(UTILS, "review-marker.py"), os.path.join(self.repo, "utils"))
        os.makedirs(os.path.join(self.repo, ".github/scripts"))
        shutil.copy(os.path.join(ROOT, ".github/scripts/bits_review_gate_policy.py"),
                    os.path.join(self.repo, ".github/scripts"))
        self.write("ddprof-lib/src/main/cpp/a.cpp", "int a;\n")
        self.write("AGENTS.md", "x\n")
        self.git("add", "-A")
        self.git("commit", "-qm", "init")
        self.git("push", "-q", "origin", "main")
        self.git("checkout", "-qb", "topic")
        self.write("ddprof-lib/src/main/cpp/a.cpp", "int a = 1;\n")
        self.git("commit", "-qam", "topic")
        self.git("push", "-q", "-u", "origin", "topic")
        self.head = self.git("rev-parse", "HEAD")
        self.env = dict(os.environ, BABYSIT_GH=os.path.join(UTILS, "tests", "fake_gh.py"),
                        FAKE_GH_DIR=self.gh_dir, BABYSIT_REPO="o/r", BABYSIT_SLEEP_SCALE="0")
        self.routes({})

    def write(self, path, text, root=None):
        with open(os.path.join(root or self.repo, path), "w") as f:
            f.write(text)

    def git(self, *args, cwd=None):
        return sh("git", *args, cwd=cwd or self.repo).stdout.strip()

    def routes(self, extra, head=None, pr_state="open"):
        pr = {"state": pr_state, "merged": False, "head": {"sha": head or self.head, "ref": "topic"},
              "base": {"ref": "main"}, "user": {"login": "alice"}, "mergeable_state": "clean", "draft": False}
        r = {"GET repos/o/r/pulls/1": pr, "GET user": {"id": SELF},
             "GET repos/o/r/pulls/1/comments": [], "GET repos/o/r/pulls/1/reviews": [],
             "GET repos/o/r/issues/1/comments": [],
             "GET repos/o/r/commits/%s/check-runs" % (head or self.head): {"check_runs": []},
             "GET repos/o/r/commits/%s/status" % (head or self.head): {"statuses": []}}
        r.update(extra)
        with open(os.path.join(self.gh_dir, "routes.json"), "w") as f:
            json.dump(r, f)

    def calls(self):
        path = os.path.join(self.gh_dir, "calls.jsonl")
        if not os.path.exists(path):
            return []
        with open(path) as f:
            return [json.loads(line) for line in f]

    def cli(self, *args, cwd=None, rc=0):
        res = sh(sys.executable, os.path.join(UTILS, "babysit-pr.py"), *args, "--pr", "1",
                 cwd=cwd or self.repo, env=self.env, check=False)
        self.assertEqual(res.returncode, rc, res.stdout + res.stderr)
        return json.loads(res.stdout)

    def worker(self):
        wt = os.path.join(self.tmp, "wt")
        self.git("worktree", "add", "-q", "-b", "topic-babysit", wt, "origin/topic")
        return wt

    def state_path(self):
        return os.path.join(self.repo, ".git", "babysit-pr", "pr-1.json")

    def edit_state(self, **kw):
        with open(self.state_path()) as f:
            st = json.load(f)
        st.update(kw)
        with open(self.state_path(), "w") as f:
            json.dump(st, f)

    def stage_fix(self, wt, path="ddprof-lib/src/main/cpp/a.cpp", scope=None, rc=0, replies=None,
                  reviewers=()):
        self.write(path, "int a = 2;\n", root=wt)
        for name, text in (("sum", "fix the bug\n"), ("msg", "Fix a\n"),
                           ("rep", json.dumps(replies or [{"to": 10, "kind": "inline", "body": "Fixed in {commit}."}]))):
            self.write(os.path.join(self.tmp, name), text, root="/")
        return self.cli("stage-handoff", "--kind", "fix", "--summary-file", os.path.join(self.tmp, "sum"),
                        "--message-file", os.path.join(self.tmp, "msg"), "--replies-file",
                        os.path.join(self.tmp, "rep"), "--scope", *(scope or [path]),
                        *(["--reviewers", *reviewers] if reviewers else []), cwd=wt, rc=rc)

    def write_marker(self):
        sh(sys.executable, "utils/review-marker.py", "write", "--tool", "t", "--session", "s",
           "--base", "origin/main", cwd=self.repo)

    def test_start_dedupes_live_run(self):
        self.assertEqual(self.cli("start")["result"], "started")
        self.assertFalse([c for c in self.calls() if "/labels" in c["key"]])
        self.assertEqual(self.cli("start", rc=3)["result"], "live")

    def test_stage_rejects_outside_allowlist_and_scope(self):
        self.cli("start")
        wt = self.worker()
        out = self.stage_fix(wt, path="AGENTS.md", rc=1)
        self.assertIn("allowlist", out["reason"])
        self.assertEqual(self.git("diff", "--cached", "--name-only", cwd=wt), "")
        self.git("checkout", "-q", "--", "AGENTS.md", cwd=wt)
        out = self.stage_fix(wt, scope=["other.cpp"], rc=1)
        self.assertIn("declared scope", out["reason"])
        self.assertEqual(self.cli("status")["status"], "running")

    def test_fix_flow_pushes_before_replying(self):
        self.cli("start")
        wt = self.worker()
        self.assertEqual(self.stage_fix(wt)["files"], ["ddprof-lib/src/main/cpp/a.cpp"])
        self.assertEqual(self.cli("start", rc=4)["result"], "handoff_pending")
        self.assertEqual(self.cli("push-and-reply", rc=1)["result"], "refused")
        commit = self.cli("apply-handoff")["commit"]
        out = self.cli("push-and-reply", rc=1)
        self.assertIn("review marker", out["reason"])
        self.assertEqual(self.git("rev-parse", "origin/topic"), self.head)
        self.write_marker()
        n = len(self.calls())
        out = self.cli("push-and-reply")
        self.assertEqual(out["commit"], commit)
        self.assertEqual(self.git("ls-remote", "origin", "refs/heads/topic").split()[0], commit)
        replies = [c for c in self.calls()[n:] if c["key"] == "POST repos/o/r/pulls/1/comments/10/replies"]
        self.assertEqual(len(replies), 1)
        self.assertEqual([c["key"] for c in self.calls()[n:]].count("GET repos/o/r/pulls/1/comments"), 1)
        self.assertIn(commit[:9], replies[0]["body"]["body"])
        self.assertTrue(replies[0]["body"]["body"].endswith(P.SIGNATURE))
        st = self.cli("status")
        self.assertEqual((st["status"], st["expected_head"], st["fix_rounds_used"]), ("running", commit, 1))
        self.assertIn("\ngpgsig ", self.git("cat-file", "commit", commit))
        self.assertEqual(self.cli("start")["result"], "resumed")

    def test_lease_rejection_posts_no_reply(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.cli("apply-handoff")
        self.write_marker()
        other = os.path.join(self.tmp, "other")
        sh("git", "clone", "-q", "-b", "topic", self.origin, other, cwd=self.tmp)
        sh("git", "-c", "user.email=x@x", "-c", "user.name=x", "commit", "-q", "--allow-empty", "-m", "x", cwd=other)
        sh("git", "push", "-q", "origin", "topic", cwd=other)
        out = self.cli("push-and-reply", rc=1)
        self.assertIn("push refused", out["reason"])
        self.assertFalse([c for c in self.calls() if c["key"].endswith("/replies")])
        self.assertEqual(self.cli("status")["pending_handoff"]["phase"], "committed")

    def test_interrupted_replies_resume_without_repush(self):
        self.cli("start")
        replies = [{"to": 10, "kind": "inline", "body": "Fixed in {commit}."},
                   {"to": 11, "kind": "inline", "body": "Also {commit}."}]
        self.stage_fix(self.worker(), replies=replies)
        self.cli("apply-handoff")
        self.write_marker()
        with open(os.path.join(self.gh_dir, "fail.json"), "w") as f:
            json.dump({"POST repos/o/r/pulls/1/comments/11/replies": ["gh: HTTP 500", 1]}, f)
        self.cli("push-and-reply", rc=2)
        st = self.cli("status")
        self.assertEqual((st["pending_handoff"]["phase"], st["pending_handoff"]["posted"]), ("pushed", [10]))
        self.assertEqual(self.cli("stop", "--reason", "x", rc=1)["result"], "refused")
        self.cli("push-and-reply")
        keys = [c["key"] for c in self.calls()]
        self.assertEqual(keys.count("POST repos/o/r/pulls/1/comments/10/replies"), 1)
        self.assertEqual(keys.count("POST repos/o/r/pulls/1/comments/11/replies"), 2)

    def test_unsigned_commit_refused_and_tree_restored(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.git("config", "commit.gpgsign", "false")
        self.assertIn("unsigned", self.cli("apply-handoff", rc=1)["reason"])
        self.assertEqual((self.git("rev-parse", "HEAD"), self.git("status", "--porcelain", "--untracked-files=no")),
                         (self.head, ""))
        self.git("config", "commit.gpgsign", "true")
        self.assertEqual(self.cli("apply-handoff")["result"], "committed")

    def test_apply_adopts_commit_left_by_crash(self):
        self.cli("start")
        self.stage_fix(self.worker())
        with open(self.state_path()) as f:
            patch = json.load(f)["pending_handoff"]["patch"]
        self.git("apply", "--index", patch)
        self.git("commit", "-qm", "Fix a")
        out = self.cli("apply-handoff")
        self.assertEqual((out["result"], out["commit"]), ("adopted", self.git("rev-parse", "HEAD")))
        self.assertEqual(self.cli("status")["pending_handoff"]["phase"], "committed")

    def test_last_round_below_cap_pushes(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.cli("apply-handoff")
        self.write_marker()
        self.edit_state(fix_rounds_used=1)
        self.assertEqual(self.cli("push-and-reply")["fix_rounds_left"], 0)

    def test_round_cap_reached(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.cli("apply-handoff")
        self.write_marker()
        self.edit_state(fix_rounds_used=2)
        self.assertIn("round cap", self.cli("push-and-reply", rc=1)["reason"])

    def test_missing_trusted_ref_fails_closed(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.cli("apply-handoff")
        self.write_marker()
        self.git("update-ref", "-d", "refs/remotes/origin/main")
        self.assertIn("origin/main", self.cli("push-and-reply", rc=2)["reason"])
        self.assertEqual(self.git("ls-remote", "origin", "refs/heads/topic").split()[0], self.head)

    def test_empty_bot_allowlist_fails_closed(self):
        self.cli("start")
        self.git("checkout", "-q", "main")
        self.write(".github/scripts/bits_review_gate_policy.py", "TRUSTED_BOT_IDS = compute()\n")
        self.git("commit", "-qam", "drift")
        self.git("push", "-q", "origin", "main")
        self.assertIn("TRUSTED_BOT_IDS", self.cli("wait", "--immediate", "--max-wait", "0", rc=2)["reason"])

    def test_reviewers_limited_to_blocking_authors(self):
        self.cli("start")
        wt = self.worker()
        self.assertIn("CHANGES_REQUESTED", self.stage_fix(wt, reviewers=["eve"], rc=1)["reason"])
        self.routes({"GET repos/o/r/pulls/1/reviews": [{"id": 1, "user": WRITER, "state": "CHANGES_REQUESTED"}]})
        self.stage_fix(wt, reviewers=["bob"])
        self.assertEqual(self.cli("status")["pending_handoff"]["reviewers"], ["bob"])

    def test_resolve_decision_adopts_new_head(self):
        self.cli("start")
        self.write(os.path.join(self.tmp, "sum"), "head moved\n", root="/")
        self.cli("stage-handoff", "--kind", "decision", "--summary-file", os.path.join(self.tmp, "sum"))
        self.routes({}, head="c" * 40)
        self.cli("resolve-handoff", "--note", "keep going")
        st = self.cli("status")
        self.assertEqual((st["status"], st["expected_head"], st["heartbeat_at"]), ("running", "c" * 40, 0))

    def test_stop_guards_unpushed_fix(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.cli("apply-handoff")
        self.assertIn("not pushed", self.cli("stop", "--reason", "x", rc=1)["reason"])

    def test_stop_reports_staged_patch(self):
        self.cli("start")
        self.stage_fix(self.worker())
        out = self.cli("stop", "--reason", "x")
        self.assertTrue(os.path.exists(out["summary"]["pending_handoff"]["patch"]))

    def test_failed_status_post_leaves_resumable_run(self):
        with open(os.path.join(self.gh_dir, "fail.json"), "w") as f:
            json.dump({"POST repos/o/r/issues/1/comments": ["gh: HTTP 502", 1]}, f)
        self.assertEqual(self.cli("start", rc=2)["result"], "error")
        st = self.cli("status")
        self.assertEqual((st["status"], st["heartbeat_at"], st["status_comment_id"]), ("running", 0, None))
        self.assertEqual(self.cli("start")["result"], "resumed")
        self.assertTrue(self.cli("status")["status_comment_id"])

    def test_non_404_error_naming_404_is_not_not_found(self):
        self.cli("start")
        with open(os.path.join(self.gh_dir, "fail.json"), "w") as f:
            json.dump({"GET repos/o/r/collaborators/bob/permission": ["gh: id 404 rate limited (HTTP 403)", 3]}, f)
        self.routes({"GET repos/o/r/pulls/1/comments": [{"id": 10, "user": WRITER, "body": "bug"}]})
        self.assertEqual(self.cli("wait", "--immediate", "--max-wait", "0", rc=2)["result"], "error")

    def test_rerun_once_per_run_and_recorded_on_failure(self):
        self.cli("start")
        url = "https://github.com/o/r/actions/runs/77/job/%d"
        runs = [{"name": "j%d" % i, "status": "completed", "conclusion": "failure", "details_url": url % i}
                for i in range(3)]
        self.routes({"GET repos/o/r/commits/%s/check-runs" % self.head: {"check_runs": runs}})
        with open(os.path.join(self.gh_dir, "fail.json"), "w") as f:
            json.dump({"POST repos/o/r/actions/runs/77/rerun-failed-jobs": ["gh: HTTP 502", 1]}, f)
        self.assertEqual(self.cli("wait", "--immediate", "--max-wait", "0", rc=2)["result"], "error")
        self.assertEqual(self.cli("status")["retried_runs"], [77])
        out = self.cli("wait", "--immediate", "--max-wait", "0")
        self.assertEqual(sorted(e["check"] for e in out["events"]), ["j0", "j1", "j2"])
        keys = [c["key"] for c in self.calls()]
        self.assertEqual(keys.count("POST repos/o/r/actions/runs/77/rerun-failed-jobs"), 1)

    def test_already_running_rerun_is_retried_later(self):
        self.cli("start")
        runs = [{"name": "j", "status": "completed", "conclusion": "failure",
                 "details_url": "https://github.com/o/r/actions/runs/77/job/1"}]
        self.routes({"GET repos/o/r/commits/%s/check-runs" % self.head: {"check_runs": runs}})
        with open(os.path.join(self.gh_dir, "fail.json"), "w") as f:
            json.dump({"POST repos/o/r/actions/runs/77/rerun-failed-jobs":
                       ["gh: This workflow is already running (HTTP 403)", 1]}, f)
        self.cli("wait", "--immediate", "--max-wait", "0")
        self.assertEqual(self.cli("status")["retried_runs"], [])
        self.cli("wait", "--immediate", "--max-wait", "0")
        self.assertEqual(self.cli("status")["retried_runs"], [77])

    def test_failed_bits_trigger_is_retried(self):
        self.cli("start")
        self.routes({"GET repos/o/r/commits/%s/check-runs" % self.head:
                     {"check_runs": [{"name": "b", "status": "completed", "conclusion": "success"}]}})
        with open(os.path.join(self.gh_dir, "fail.json"), "w") as f:
            json.dump({"POST repos/o/r/issues/1/comments": ["gh: HTTP 502", 1]}, f)
        self.cli("wait", "--immediate", "--max-wait", "0", rc=2)
        self.assertEqual(self.cli("status")["bits_triggered"], [])
        self.cli("wait", "--immediate", "--max-wait", "0")
        self.assertEqual(self.cli("status")["bits_triggered"], [self.head])

    def test_push_already_landed_is_adopted(self):
        self.cli("start")
        self.stage_fix(self.worker())
        commit = self.cli("apply-handoff")["commit"]
        self.write_marker()
        self.git("push", "-q", "origin", "HEAD:topic")
        self.assertEqual(self.cli("push-and-reply")["commit"], commit)
        self.assertIn("POST repos/o/r/pulls/1/comments/10/replies", [c["key"] for c in self.calls()])

    def test_rebase_handoff_requires_rebase(self):
        self.cli("start")
        self.write(os.path.join(self.tmp, "sum"), "conflict\n", root="/")
        self.cli("stage-handoff", "--kind", "rebase", "--summary-file", os.path.join(self.tmp, "sum"))
        self.write_marker()
        self.assertIn("not rebased", self.cli("push-and-reply", rc=1)["reason"])

    def test_adoption_rejects_different_content(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.write("ddprof-lib/src/main/cpp/a.cpp", "int a = 3;\n")
        self.git("commit", "-qam", "other")
        self.assertIn("not the handoff base", self.cli("apply-handoff", rc=1)["reason"])

    def test_adoption_refused_without_patch_file(self):
        self.cli("start")
        self.stage_fix(self.worker())
        with open(self.state_path()) as f:
            patch = json.load(f)["pending_handoff"]["patch"]
        self.git("apply", "--index", patch)
        self.git("commit", "-qm", "Fix a")
        os.unlink(patch)
        self.assertIn("not the handoff base", self.cli("apply-handoff", rc=1)["reason"])

    def test_issue_reply_is_idempotent(self):
        self.cli("start")
        own = {"id": 50, "user": {"id": SELF}, "body": "x <!-- babysit-pr reply-to:20 -->\n" + P.SIGNATURE}
        self.routes({"GET repos/o/r/issues/1/comments": [own]})
        self.write(os.path.join(self.tmp, "b"), "answer", root="/")
        out = self.cli("reply", "--to", "20", "--kind", "issue", "--body-file", os.path.join(self.tmp, "b"))
        self.assertEqual(out["result"], "already_replied")
        self.routes({})
        self.cli("reply", "--to", "21", "--kind", "issue", "--body-file", os.path.join(self.tmp, "b"))
        posted = [c for c in self.calls() if c["key"] == "POST repos/o/r/issues/1/comments"][-1]
        self.assertIn("reply-to:21 -->\n" + P.SIGNATURE, posted["body"]["body"])

    def test_stop_summary_lists_acked_events(self):
        self.cli("start")
        self.routes({"GET repos/o/r/pulls/1/comments": [{"id": 10, "user": AUTHOR, "body": "bug"}]})
        self.cli("wait", "--immediate", "--max-wait", "0")
        self.cli("ack", "thread:10")
        self.assertIn("thread:10", self.cli("stop", "--reason", "x")["summary"]["acked"])

    def test_green_done_waits_for_inbox(self):
        self.cli("start")
        green = {"GET repos/o/r/commits/%s/check-runs" % self.head:
                 {"check_runs": [{"name": "b", "status": "completed", "conclusion": "success"}]},
                 "GET repos/o/r/commits/%s/status" % self.head:
                 {"statuses": [{"context": P.BITS_CONTEXT, "state": "success"}]}}
        self.routes(dict(green, **{"GET repos/o/r/issues/1/comments": [{"id": 20, "user": AUTHOR, "body": "q?"}]}))
        self.assertEqual(self.cli("wait", "--immediate", "--max-wait", "0")["outcome"], "action_needed")
        out = self.cli("wait", "--immediate", "--max-wait", "0")
        self.assertEqual((out["outcome"], self.cli("status")["status"]), ("action_needed", "running"))
        self.cli("ack", "comment:20")
        self.assertEqual(self.cli("wait", "--immediate", "--max-wait", "0")["outcome"], "green_done")

    def test_signature_in_message_is_not_a_signature(self):
        self.cli("start")
        self.stage_fix(self.worker())
        with open(self.state_path()) as f:
            st = json.load(f)
        st["pending_handoff"]["message"] = "Fix a\n\ngpgsig fake\n"
        with open(self.state_path(), "w") as f:
            json.dump(st, f)
        self.git("config", "commit.gpgsign", "false")
        self.assertIn("unsigned", self.cli("apply-handoff", rc=1)["reason"])

    def test_push_refused_after_cap(self):
        self.cli("start")
        self.stage_fix(self.worker())
        self.cli("apply-handoff")
        self.write_marker()
        self.edit_state(deadline_at=1)
        self.assertIn("two-hour cap", self.cli("push-and-reply", rc=1)["reason"])
        self.assertEqual(self.git("ls-remote", "origin", "refs/heads/topic").split()[0], self.head)

    def test_no_poll_once_slice_ended(self):
        self.cli("start")
        self.edit_state(next_poll_at=0)
        n = len(self.calls())
        self.assertEqual(self.cli("wait", "--max-wait", "0")["outcome"], "continue")
        self.assertEqual(self.calls()[n:], [])

    def load_cli(self):
        spec = importlib.util.spec_from_file_location("babysit_pr_cli", os.path.join(UTILS, "babysit-pr.py"))
        mod = importlib.util.module_from_spec(spec)
        old = dict(os.environ)
        os.environ.update(self.env)
        self.addCleanup(lambda: (os.environ.clear(), os.environ.update(old)))
        cwd = os.getcwd()
        os.chdir(self.repo)
        self.addCleanup(os.chdir, cwd)
        spec.loader.exec_module(mod)
        return mod

    def test_budget_caps_every_call(self):
        mod = self.load_cli()
        mod._budget_end = mod.time.time() + 1.5
        with self.assertRaises(mod.OutOfTime) as cm:
            mod.run(["sleep", "5"], 60)
        self.assertTrue(cm.exception.started)
        mod._budget_end = mod.time.time() - 1
        with self.assertRaises(mod.OutOfTime) as cm:
            mod.run(["true"], 60)
        self.assertFalse(cm.exception.started)

    def test_budget_exhaustion_ends_slice_and_keeps_rerun_retriable(self):
        self.cli("start")
        runs = [{"name": "j", "status": "completed", "conclusion": "failure",
                 "details_url": "https://github.com/o/r/actions/runs/77/job/1"}]
        self.routes({"GET repos/o/r/commits/%s/check-runs" % self.head: {"check_runs": runs}})
        mod = self.load_cli()
        real = mod.gh_api

        def gh_api(path, method="GET", **kw):
            if path.endswith("/rerun-failed-jobs"):
                raise mod.OutOfTime(started=False)
            return real(path, method, **kw)
        mod.gh_api = gh_api
        with contextlib.redirect_stdout(io.StringIO()) as out:
            self.assertEqual(mod.main(["wait", "--pr", "1", "--immediate", "--max-wait", "0"]), 0)
        self.assertEqual(json.loads(out.getvalue())["outcome"], "continue")
        with open(self.state_path()) as f:
            self.assertEqual(json.load(f)["retried_runs"], [])

    def test_commit_timeout_restores_base_tree(self):
        self.cli("start")
        self.stage_fix(self.worker())
        mod = self.load_cli()

        def timed_out(h):
            raise mod.EnvError("timed out after 120s: git commit")
        mod.commit_handoff = timed_out
        with contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(mod.main(["apply-handoff", "--pr", "1"]), 2)
        self.assertEqual((self.git("rev-parse", "HEAD"), self.git("status", "--porcelain", "--untracked-files=no")),
                         (self.head, ""))

    def test_rebase_check_fetches_base(self):
        self.cli("start")
        other = os.path.join(self.tmp, "other")
        sh("git", "clone", "-q", self.origin, other, cwd=self.tmp)
        sh("git", "-c", "user.email=x@x", "-c", "user.name=x", "commit", "-q", "--allow-empty", "-m", "x", cwd=other)
        sh("git", "push", "-q", "origin", "main", cwd=other)
        self.write(os.path.join(self.tmp, "sum"), "conflict\n", root="/")
        self.cli("stage-handoff", "--kind", "rebase", "--summary-file", os.path.join(self.tmp, "sum"))
        self.git("commit", "-q", "--allow-empty", "-m", "rebased onto the stale base")
        self.write_marker()
        self.assertIn("not rebased", self.cli("push-and-reply", rc=1)["reason"])

    def test_reply_refuses_commit_placeholder(self):
        self.cli("start")
        self.write(os.path.join(self.tmp, "b"), "Fixed in {commit}", root="/")
        out = self.cli("reply", "--to", "10", "--kind", "inline", "--body-file", os.path.join(self.tmp, "b"), rc=1)
        self.assertIn("{commit}", out["reason"])

    def test_wait_returns_inbox_until_acked(self):
        self.cli("start")
        self.routes({"GET repos/o/r/pulls/1/comments": [{"id": 10, "user": AUTHOR, "body": "bug"}]})
        out = self.cli("wait", "--immediate", "--max-wait", "0")
        self.assertEqual([e["key"] for e in out["events"]], ["thread:10"])
        self.assertEqual(self.cli("wait", "--max-wait", "0")["outcome"], "action_needed")
        self.cli("ack", "thread:10")
        self.assertEqual(self.cli("wait", "--max-wait", "0")["outcome"], "continue")

    def test_wait_stops_on_closed_pr(self):
        self.cli("start")
        self.routes({}, pr_state="closed")
        out = self.cli("wait", "--immediate", "--max-wait", "0")
        self.assertEqual((out["outcome"], out["summary"]["stop_reason"]), ("stop", "PR closed"))
        self.assertFalse([c for c in self.calls() if "/labels" in c["key"]])
        self.assertEqual(self.cli("start", rc=1)["result"], "refused")

    def test_worker_marker_written_in_worktree_only(self):
        self.cli("start")
        wt = self.worker()
        self.cli("wait", "--max-wait", "0", cwd=wt)
        with open(os.path.join(wt, "build", "babysit-pr-1.json")) as f:
            self.assertEqual(json.load(f), {"pr": 1, "branch": "topic-babysit", "status": "running", "scope": []})
        self.assertFalse(os.path.exists(os.path.join(self.repo, "build")))


if __name__ == "__main__":
    unittest.main()
