#!/usr/bin/env python3
# Copyright 2026, Datadog, Inc.
"""Deterministic driver of the babysit-pr skill (see utils/README.md).

Owns every mechanical step of a PR babysitting run: the shared run state, GitHub REST
polling, the trust gate, CI reruns and Bits triggers, the status comment, the worker's
fix handoff and the parent's apply, push and reply transaction. The LLM worker only
triages the events `wait` returns, fixes code, and drafts replies. Every command prints
one JSON object on stdout.

Exit codes: 0 ok, 1 refused (the JSON says why), 2 usage or environment error,
3 a live run already owns the PR, 4 a handoff awaits the parent.
"""

import argparse
import contextlib
import fcntl
import functools
import importlib.util
import json
import os
import subprocess
import sys
import tempfile
import time

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import babysit_pr_policy as policy  # noqa: E402

REPO = os.environ.get("BABYSIT_REPO", "datadog/java-profiler")
GH = os.environ.get("BABYSIT_GH") or (
    "/opt/dogbrew/shims/bin/gh" if os.access("/opt/dogbrew/shims/bin/gh", os.X_OK) else "gh")
CAP_S = 2 * 3600
MAX_ROUNDS = 2
# A worker calls `wait` at least every few minutes while idle but may spend longer on one
# fix; only a heartbeat older than this marks the run dead for a second launcher.
DEAD_AFTER_S = 45 * 60
MAX_WAIT_S = 480  # one wait slice; stays below the 600 s default bash tool timeout
GH_TIMEOUT_S = 60
GIT_TIMEOUT_S = 120
PUSH_TIMEOUT_S = 300
READ_RETRIES = 3
CARRIED = ("bits_triggered", "bits_rerequested", "replied", "retried_runs")


class Refused(Exception):
    pass


class EnvError(Exception):
    pass


class OutOfTime(EnvError):
    """The wait slice's budget ran out. started tells whether the call reached the
    subprocess, i.e. whether a write may have been applied."""

    def __init__(self, started):
        super().__init__("wait slice budget exhausted")
        self.started = started


# Wall-clock end of the current wait slice, or None outside `wait`. Every subprocess
# attempt is capped at the time left, so one slice cannot overrun the bash tool timeout.
_budget_end = None


def emit(obj):
    print(json.dumps(obj, indent=1, sort_keys=True))


def sleep(seconds):
    time.sleep(seconds * float(os.environ.get("BABYSIT_SLEEP_SCALE", "1")))


def run(cmd, timeout, retries=1, stdin=None, cwd=None):
    """(rc, stdout, stderr). A timeout counts as a failed attempt; after the last attempt
    it raises EnvError so no caller mistakes a hung call for an answer."""
    for attempt in range(retries):
        limit = timeout
        if _budget_end is not None:
            left = _budget_end - time.time()
            if left < 1:
                raise OutOfTime(started=attempt > 0)
            limit = min(timeout, left)
        try:
            res = subprocess.run(cmd, input=stdin, capture_output=True, text=True,
                                 timeout=limit, cwd=cwd, errors="replace")
        except subprocess.TimeoutExpired:
            if limit < timeout:
                raise OutOfTime(started=True)
            if attempt + 1 == retries:
                raise EnvError("timed out after %ds: %s" % (timeout, " ".join(cmd[:4])))
        else:
            if res.returncode == 0 or attempt + 1 == retries:
                return res.returncode, res.stdout, res.stderr
        sleep(2 ** attempt)
    raise AssertionError("unreachable")


def git(*args, timeout=GIT_TIMEOUT_S, check=True, cwd=None):
    rc, out, err = run(["git", *args], timeout, cwd=cwd)
    if check and rc != 0:
        raise Refused("git %s failed: %s" % (args[0], err.strip()))
    return out.strip() if rc == 0 else None


def gh_api(path, method="GET", payload=None, jq=None, paginate=False, ok404=False):
    """Parsed JSON of one REST call. Reads retry; writes run once, since a retried POST
    that timed out after the server applied it would post twice."""
    cmd = [GH, "api", "-X", method, "-H", "Accept: application/vnd.github+json", path]
    if paginate:
        cmd.append("--paginate")
    if jq:
        cmd += ["--jq", jq]
    if payload is not None:
        cmd += ["--input", "-"]
    rc, out, err = run(cmd, GH_TIMEOUT_S, retries=READ_RETRIES if method == "GET" else 1,
                       stdin=json.dumps(payload) if payload is not None else None)
    if rc != 0:
        if ok404 and "HTTP 404" in err:
            return None
        raise EnvError("gh api %s %s failed: %s" % (method, path, err.strip()[:300]))
    if jq:
        return [json.loads(line) for line in out.splitlines() if line.strip()]
    return json.loads(out) if out.strip() else None


# ---- state -------------------------------------------------------------------------

def state_dir():
    common = git("rev-parse", "--path-format=absolute", "--git-common-dir")
    d = os.path.join(common, "babysit-pr")
    os.makedirs(d, exist_ok=True)
    return d


@contextlib.contextmanager
def locked(pr):
    """(load, save) under an exclusive flock shared by every worktree of the clone."""
    d = state_dir()
    path = os.path.join(d, "pr-%d.json" % pr)
    with open(os.path.join(d, "pr-%d.lock" % pr), "w") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        box = {}
        try:
            with open(path) as f:
                box["state"] = json.load(f)
        except FileNotFoundError:
            box["state"] = None

        def save(st):
            fd, tmp = tempfile.mkstemp(dir=d, prefix=".pr-%d." % pr)
            with os.fdopen(fd, "w") as f:
                json.dump(st, f, indent=1, sort_keys=True)
            os.replace(tmp, path)
            box["state"] = st
        yield box, save


def require(box, pr):
    if box["state"] is None:
        raise Refused("no babysit run recorded for PR %d; run start first" % pr)
    return box["state"]


def hhmm(t=None):
    return time.strftime("%H:%M", time.gmtime(t if t is not None else time.time()))


def log(st, tag, fact):
    st["run_log"].append({"t": hhmm(), "tag": tag, "fact": fact})


def publish_status(st):
    body = policy.render_status(st, hhmm())
    if st.get("status_comment_id"):
        gh_api("repos/%s/issues/comments/%d" % (REPO, st["status_comment_id"]), "PATCH", {"body": body})
    else:
        st["status_comment_id"] = gh_api("repos/%s/issues/%d/comments" % (REPO, st["pr"]), "POST",
                                         {"body": body})["id"]


def trusted_source(path):
    """origin/main's copy of path. The checkout may be an untrusted branch, so a missing
    ref or file is an error, never a fallback to the checkout's copy."""
    rc, out, err = run(["git", "show", "refs/remotes/origin/main:" + path], GIT_TIMEOUT_S)
    if rc != 0:
        raise EnvError("cannot read %s from origin/main (fetch origin first): %s" % (path, err.strip()))
    return out


@functools.lru_cache(maxsize=1)
def allowlist():
    path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "babysit-scope-guard.py")
    spec = importlib.util.spec_from_file_location("babysit_scope_guard", path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod.ALLOWLIST


def check_files(files, scope):
    outside = [f for f in files if not allowlist().match(f)]
    if outside:
        raise Refused("files outside the source/test allowlist (the parent session's, "
                      "never the worker's): %s" % ", ".join(outside))
    undeclared = [f for f in files if f not in scope]
    if undeclared:
        raise Refused("files not in the declared scope: %s" % ", ".join(undeclared))


# ---- commands ----------------------------------------------------------------------

def cmd_start(a):
    pr = gh_api("repos/%s/pulls/%d" % (REPO, a.pr))
    if pr["state"] != "open":
        raise Refused("PR %d is %s" % (a.pr, "merged" if pr.get("merged") else "closed"))
    now = time.time()
    with locked(a.pr) as (box, save):
        st = box["state"]
        if st and st["status"] == "running" and now - st["heartbeat_at"] < DEAD_AFTER_S:
            emit({"result": "live", "heartbeat_age_s": int(now - st["heartbeat_at"])})
            return 3
        if st and st["status"] == "waiting_parent":
            emit({"result": "handoff_pending", "handoff": st["pending_handoff"]})
            return 4
        fresh = st is None or st["status"] == "stopped"
        if fresh:
            carried = {k: (st or {}).get(k, []) for k in CARRIED}
            branch = pr["head"]["ref"]
            st = dict(carried, pr=a.pr, branch=branch, base=pr["base"]["ref"],
                      remote=git("config", "branch.%s.remote" % branch, check=False) or "origin",
                      parent_checkout=git("rev-parse", "--show-toplevel"),
                      self_id=gh_api("user")["id"], started_at=now, started_hhmm=hhmm(now),
                      deadline_at=now + CAP_S, fix_rounds_used=0, expected_head=pr["head"]["sha"],
                      status_comment_id=None, run_log=[], surfaced=[], inbox={}, untrusted={},
                      perm_cache={}, facts={}, idle_polls=0, next_poll_at=0, pushed=[],
                      flags=[], pending_handoff=None, acked={})
            log(st, "started", "head `%s`" % st["expected_head"][:9])
        else:
            st["parent_checkout"] = git("rev-parse", "--show-toplevel")
            log(st, "resumed", "worker relaunched on `%s`" % st["expected_head"][:9])
        # Saved before the status-comment POST, with heartbeat 0: if that POST fails, the
        # next start resumes this run with its deadline instead of starting a new one.
        st["status"], st["heartbeat_at"] = "running", 0
        save(st)
        publish_status(st)
        st["heartbeat_at"] = now
        save(st)
    dirty = git("status", "--porcelain", "--untracked-files=no")
    emit({"result": "started" if fresh else "resumed", "branch": st["branch"],
          "expected_head": st["expected_head"], "deadline_at": int(st["deadline_at"]),
          "fix_rounds_left": MAX_ROUNDS - st["fix_rounds_used"],
          "warning": "parent checkout has uncommitted changes" if dirty else None})
    return 0


def snapshot(pr_number):
    pr = gh_api("repos/%s/pulls/%d" % (REPO, pr_number))
    head = pr["head"]["sha"]
    base = "repos/%s/" % REPO
    return {
        "pr": {"state": pr["state"], "merged": pr.get("merged"), "head": head,
               "mergeable_state": pr.get("mergeable_state"), "draft": pr.get("draft"),
               "author": pr["user"]["login"]},
        "check_runs": gh_api(base + "commits/%s/check-runs?per_page=100" % head,
                             jq=".check_runs[]", paginate=True),
        "statuses": gh_api(base + "commits/%s/status?per_page=100" % head,
                           jq=".statuses[]", paginate=True),
        "inline_comments": gh_api(base + "pulls/%d/comments?per_page=100" % pr_number,
                                  jq=".[]", paginate=True),
        "reviews": gh_api(base + "pulls/%d/reviews?per_page=100" % pr_number, jq=".[]", paginate=True),
        "issue_comments": gh_api(base + "issues/%d/comments?per_page=100" % pr_number,
                                 jq=".[]", paginate=True),
    }


def make_trusted(st, author):
    ids = policy.parse_trusted_bot_ids(trusted_source(".github/scripts/bits_review_gate_policy.py"))
    if not ids:  # an empty set would silently demote every Bits finding to untrusted
        raise EnvError("no TRUSTED_BOT_IDS literal in origin/main's bits_review_gate_policy.py")

    def trusted(user):
        login = (user or {}).get("login")
        if login and (user or {}).get("type") != "Bot" and login != author and login not in st["perm_cache"]:
            res = gh_api("repos/%s/collaborators/%s/permission" % (REPO, login), ok404=True)
            st["perm_cache"][login] = (res or {}).get("permission")
        return policy.trust_of(user, author, st["perm_cache"].get(login), ids)
    return trusted


def ensure_worker_marker(st):
    """The worker worktree's running marker (scope []) keeps .githooks/pre-push
    fail-closed: a direct push from the worktree is refused. The worker never pushes."""
    top = git("rev-parse", "--show-toplevel")
    branch = git("symbolic-ref", "-q", "--short", "HEAD", check=False)
    if top == st["parent_checkout"] or not branch:
        return
    path = os.path.join(top, "build", "babysit-pr-%d.json" % st["pr"])
    os.makedirs(os.path.dirname(path), exist_ok=True)
    fd, tmp = tempfile.mkstemp(dir=os.path.dirname(path))
    with os.fdopen(fd, "w") as f:
        json.dump({"pr": st["pr"], "branch": branch, "status": "running", "scope": []}, f)
    os.replace(tmp, path)


def poll_once(pr_number, now):
    """One poll under the lock: decide, run mechanical actions, record facts. Returns the
    outcome dict to hand back, or None to keep waiting."""
    snap = snapshot(pr_number)
    with locked(pr_number) as (box, save):
        st = require(box, pr_number)
        if st["status"] != "running":
            return {"outcome": st["status"]}
        st["heartbeat_at"] = now
        state_view = dict(st, surfaced=st["surfaced"] + list(st["inbox"]))
        d = policy.decide(state_view, snap, make_trusted(st, snap["pr"]["author"]), now)
        changed = bool(d["events"])
        for act in d["actions"]:
            if act[0] == "rerun":
                # Saved before the POST: a failed or interrupted rerun must not become one
                # rerun per poll. "already running" or an unsent request: GitHub did nothing.
                st["retried_runs"].append(act[1])
                save(st)
                try:
                    gh_api("repos/%s/actions/runs/%d/rerun-failed-jobs" % (REPO, act[1]), "POST")
                except EnvError as e:
                    unsent = isinstance(e, OutOfTime) and not e.started
                    if not unsent and "already running" not in str(e):
                        raise
                    st["retried_runs"].remove(act[1])
                    save(st)
                    if unsent:
                        raise
                    continue
                changed = True
                log(st, "retried", "%s (run %d)" % (act[2], act[1]))
            else:
                # Recorded after the POST: a duplicate @datadog review is cheap, a lost one
                # stalls the run until the cap.
                gh_api("repos/%s/issues/%d/comments" % (REPO, pr_number), "POST",
                       {"body": policy.BITS_TRIGGER})
                st["bits_triggered"].append(act[1])
                changed = True
                log(st, "Bits", "review requested on `%s`" % act[1][:9])
                save(st)
        for key in ("ci", "bits"):
            if d["facts"].get(key) and d["facts"][key] != st["facts"].get(key):
                changed = True
                log(st, "CI" if key == "ci" else "Bits", "%s on `%s`" % (d["facts"][key], snap["pr"]["head"][:9]))
        st["facts"].update(d["facts"])
        for u in d["untrusted"]:
            st["untrusted"][str(u["id"])] = u
        for ev in d["events"]:
            st["inbox"][ev["key"]] = ev
        st["idle_polls"] = 0 if changed else st["idle_polls"] + 1
        st["next_poll_at"] = now + policy.next_interval(st["idle_polls"])
        # Inbox events still need the worker; reviews and comments are not open_threads.
        if d["outcome"] == "stop" or (d["outcome"] == "green_done" and not st["inbox"]):
            reason = d["facts"].get("reason") or "CI green, Bits passed, threads answered"
            summary = finish(st, reason)
            save(st)
            return {"outcome": d["outcome"], "summary": summary}
        if changed:
            publish_status(st)
        save(st)
        if st["inbox"]:
            return inbox_result(st)
        return None


def inbox_result(st):
    return {"outcome": "action_needed", "events": sorted(st["inbox"].values(), key=lambda e: e["key"]),
            "fix_rounds_left": MAX_ROUNDS - st["fix_rounds_used"],
            "seconds_left": int(st["deadline_at"] - time.time())}


def cmd_wait(a):
    global _budget_end
    end = time.time() + min(a.max_wait, MAX_WAIT_S)
    _budget_end = time.time() + MAX_WAIT_S
    try:
        return wait_loop(a, end)
    except OutOfTime:
        emit({"outcome": "continue", "next_poll_in_s": 0})
        return 0
    finally:
        _budget_end = None


def wait_loop(a, end):
    immediate = a.immediate
    while True:
        now = time.time()
        with locked(a.pr) as (box, save):
            st = require(box, a.pr)
            if st["status"] != "running":
                emit({"outcome": st["status"], "handoff": st.get("pending_handoff")})
                return 0
            ensure_worker_marker(st)
            st["heartbeat_at"] = now
            save(st)
            if st["inbox"] and not immediate:
                emit(inbox_result(st))
                return 0
            due = st["next_poll_at"]
        if immediate or (due <= now < end):
            immediate = False
            res = poll_once(a.pr, now)
            if res:
                emit(res)
                return 0
            continue
        if now >= end:
            emit({"outcome": "continue", "next_poll_in_s": int(due - now)})
            return 0
        sleep(max(1, min(due, end) - now))


def ack_keys(st, keys):
    """Move inbox events to surfaced; the event bodies stay in acked for the stop summary."""
    for key in keys or []:
        ev = st["inbox"].pop(key, None)
        if ev is None and key not in st["surfaced"]:
            raise Refused("no event %s in the inbox" % key)
        if ev is not None:
            st["acked"][key] = ev
        if key not in st["surfaced"]:
            st["surfaced"].append(key)


def cmd_ack(a):
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        ack_keys(st, a.keys)
        save(st)
    emit({"result": "acked", "keys": a.keys})
    return 0


def comments(pr, kind):
    path = "pulls/%d/comments" if kind == "inline" else "issues/%d/comments"
    return gh_api("repos/%s/%s?per_page=100" % (REPO, path % pr), jq=".[]", paginate=True)


def reply_tag(to):
    return "<!-- babysit-pr reply-to:%d -->" % to


def already_replied(c, to, kind, self_id):
    if not policy.is_own(c, self_id):
        return False
    return c.get("in_reply_to_id") == to if kind == "inline" else reply_tag(to) in (c.get("body") or "")


def post_reply(st, to, kind, body, existing=None):
    """Post one signed reply unless GitHub already holds the babysitter's reply to `to`
    (a crash between the post and the state save); records `to` in replied either way.
    existing is the PR's comments of that kind, fetched when None. The posted id or None."""
    if to in st["replied"]:
        return None
    if existing is None:
        existing = comments(st["pr"], kind)
    if any(already_replied(c, to, kind, st["self_id"]) for c in existing):
        st["replied"].append(to)
        return None
    body = body.rstrip() + "\n\n" + policy.SIGNATURE
    if kind == "inline":
        res = gh_api("repos/%s/pulls/%d/comments/%d/replies" % (REPO, st["pr"], to), "POST", {"body": body})
    else:
        body = body[:-len(policy.SIGNATURE)] + reply_tag(to) + "\n" + policy.SIGNATURE
        res = gh_api("repos/%s/issues/%d/comments" % (REPO, st["pr"]), "POST", {"body": body})
    st["replied"].append(to)
    return res["id"]


def cmd_reply(a):
    with open(a.body_file) as f:
        body = f.read()
    if "{commit}" in body:
        raise Refused("a reply naming {commit} must be queued in a fix handoff, "
                      "never posted before the push")
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        ack_keys(st, a.ack)
        posted = post_reply(st, a.to, a.kind, body)
        log(st, "answered", "%s %d" % (a.kind, a.to))
        save(st)
        publish_status(st)
        save(st)
    emit({"result": "posted" if posted else "already_replied", "id": posted})
    return 0


def cmd_trigger_bits(a):
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        head = gh_api("repos/%s/pulls/%d" % (REPO, a.pr))["head"]["sha"]
        if head in st["bits_rerequested"]:
            emit({"result": "already_requested", "head": head})
            return 0
        gh_api("repos/%s/issues/%d/comments" % (REPO, a.pr), "POST", {"body": policy.BITS_TRIGGER})
        st["bits_rerequested"].append(head)
        log(st, "Bits", "re-review requested on `%s` (%s)" % (head[:9], a.reason))
        publish_status(st)
        save(st)
    emit({"result": "requested", "head": head})
    return 0


def load_replies(path):
    if not path:
        return []
    with open(path) as f:
        replies = json.load(f)
    if not isinstance(replies, list) or not all(
            isinstance(r, dict) and isinstance(r.get("to"), int) and r.get("kind") in ("inline", "issue")
            and isinstance(r.get("body"), str) for r in replies):
        raise Refused('replies file must be a list of {"to": <id>, "kind": "inline"|"issue", "body": "..."}')
    return replies


def cmd_stage_handoff(a):
    with open(a.summary_file) as f:
        summary = f.read()
    replies = load_replies(a.replies_file)
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        if st["status"] != "running" or st.get("pending_handoff"):
            raise Refused("run is %s; a handoff is staged only from a running run" % st["status"])
        blockers = {r["user"]["login"] for r in gh_api("repos/%s/pulls/%d/reviews?per_page=100" % (REPO, a.pr),
                                                        jq=".[]", paginate=True)
                    if r.get("state") == "CHANGES_REQUESTED" and r.get("user")}
        strangers = [r for r in a.reviewers or [] if r not in blockers]
        if strangers:
            raise Refused("--reviewers may name only authors of CHANGES_REQUESTED reviews on this PR: %s"
                          % ", ".join(strangers))
        handoff = {"kind": a.kind, "summary": summary, "replies": replies, "posted": [],
                   "reviewers": a.reviewers or [], "acks": a.ack or [], "phase": "staged",
                   "base_head": st["expected_head"]}
        if a.kind == "fix":
            if not a.message_file or not a.scope:
                raise Refused("a fix handoff needs --message-file and --scope")
            if git("rev-parse", "HEAD") != st["expected_head"]:
                raise Refused("worker HEAD is not the PR head %s; stage uncommitted edits "
                              "on top of it, never a commit" % st["expected_head"][:9])
            git("add", "-A")
            files = git("diff", "--cached", "--name-only", "--no-renames", st["expected_head"]).splitlines()
            try:
                if not files:
                    raise Refused("no changes to hand off")
                check_files(files, a.scope)
            except Refused:
                git("reset", "-q")  # leave the edits unstaged, so a corrected retry sees only them
                raise
            patch = os.path.join(state_dir(), "pr-%d-%s.patch" % (a.pr, st["expected_head"][:12]))
            rc, out, err = run(["git", "diff", "--cached", "--binary", "--full-index", st["expected_head"]],
                               GIT_TIMEOUT_S)
            if rc != 0:
                raise Refused("git diff failed: %s" % err.strip())
            with open(patch, "w") as f:
                f.write(out)
            with open(a.message_file) as f:
                handoff.update(message=f.read(), files=files, scope=a.scope, patch=patch)
        ack_keys(st, handoff["acks"])
        st["status"], st["pending_handoff"] = "waiting_parent", handoff
        st["heartbeat_at"] = 0  # the worker exits now; a later start must resume, not see it live
        log(st, "handoff", "%s for the session: %s" % (a.kind, summary.strip().splitlines()[0][:120]))
        publish_status(st)
        save(st)
    emit({"result": "staged", "kind": a.kind, "files": handoff.get("files")})
    return 0


def pending(st, kinds):
    h = st.get("pending_handoff")
    if st["status"] != "waiting_parent" or not h or h["kind"] not in kinds:
        raise Refused("no pending %s handoff" % "/".join(kinds))
    return h


def cmd_apply_handoff(a):
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        h = pending(st, ("fix",))
        if h["phase"] != "staged":
            emit({"result": "already_applied", "commit": h["commit"]})
            return 0
        if git("symbolic-ref", "-q", "--short", "HEAD", check=False) != st["branch"]:
            raise Refused("check out %s in the session checkout first" % st["branch"])
        if git("status", "--porcelain", "--untracked-files=no"):
            raise Refused("session checkout has uncommitted changes; commit or stash them first")
        head = git("rev-parse", "HEAD")
        if head != h["base_head"]:
            # A crash after the commit but before the save leaves HEAD one signed commit
            # past the base with exactly the handoff's files: adopt it instead of stranding it.
            if git("rev-parse", "-q", "--verify", "HEAD^", check=False) == h["base_head"] \
                    and committed_files(h["base_head"], head) == sorted(h["files"]) and is_signed(head) \
                    and same_patch(h["base_head"], head, h["patch"]):
                h["phase"], h["commit"] = "committed", head
                save(st)
                emit({"result": "adopted", "commit": head, "review_range": "%s..%s" % (h["base_head"], head)})
                return 0
            raise Refused("session HEAD is not the handoff base %s" % h["base_head"][:9])
        git("apply", "--index", "--check", h["patch"])
        git("apply", "--index", h["patch"])
        try:
            h["commit"] = commit_handoff(h)
        except (Refused, EnvError):
            # Restore the base tree so the next apply-handoff starts clean.
            git("reset", "-q", "--soft", h["base_head"])
            git("apply", "-R", "--index", h["patch"])
            raise
        h["phase"] = "committed"
        save(st)
    emit({"result": "committed", "commit": h["commit"], "review_range": "%s..%s" % (h["base_head"], h["commit"])})
    return 0


def committed_files(base, commit):
    return sorted(git("diff", "--name-only", "--no-renames", base, commit).splitlines())


def same_patch(base, commit, patch):
    rc, out, _ = run(["git", "diff", "--binary", "--full-index", base, commit], GIT_TIMEOUT_S)
    try:
        with open(patch) as f:
            return rc == 0 and out == f.read()
    except OSError:  # a missing patch proves nothing: refuse the adoption
        return False


def is_signed(commit):
    """True when the commit object carries a signature header (gpgsig covers GPG and SSH)."""
    headers = git("cat-file", "commit", commit).split("\n\n", 1)[0]
    return "\ngpgsig " in headers


def commit_handoff(h):
    """Commit the applied patch with the checkout's signing config; the new SHA. Refuses
    (with HEAD possibly one commit past the base) on a file mismatch, a failed commit, or
    an unsigned result."""
    files = sorted(git("diff", "--cached", "--name-only", "--no-renames", "HEAD").splitlines())
    if files != sorted(h["files"]):
        raise Refused("applied files %s differ from the staged list" % files)
    check_files(files, h["scope"])
    with tempfile.NamedTemporaryFile("w", delete=False, dir=state_dir(), prefix=".msg-") as f:
        f.write(h["message"])
    try:
        rc, _, err = run(["git", "commit", "-q", "-F", f.name], GIT_TIMEOUT_S)
    finally:
        os.unlink(f.name)
    if rc != 0:
        raise Refused("git commit failed: %s" % err.strip())
    commit = git("rev-parse", "HEAD")
    if not is_signed(commit):
        raise Refused("the commit is unsigned (set commit.gpgsign); never push unsigned commits")
    return commit


def review_marker_fresh(branch):
    src = trusted_source("utils/review-marker.py")
    rc, out, err = run(["python3", "-I", "-", "check", "--branch", branch, "--commit", "HEAD"],
                       GIT_TIMEOUT_S, stdin=src)
    return rc == 0, (err or out).strip()


def cmd_push_and_reply(a):
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        h = pending(st, ("fix", "rebase"))
        if h["phase"] in ("staged", "committed") and not (h["kind"] == "fix" and h["phase"] == "staged"):
            if st["fix_rounds_used"] >= MAX_ROUNDS:
                raise Refused("fix-push round cap (%d) reached" % MAX_ROUNDS)
            if time.time() >= st["deadline_at"]:
                raise Refused("the run's two-hour cap has passed; start a new run to push")
            if gh_api("repos/%s/pulls/%d" % (REPO, a.pr))["state"] != "open":
                raise Refused("PR is no longer open")
            if git("symbolic-ref", "-q", "--short", "HEAD", check=False) != st["branch"]:
                raise Refused("check out %s in the session checkout first" % st["branch"])
            fresh, why = review_marker_fresh(st["branch"])
            if not fresh:
                raise Refused("review marker not fresh for HEAD; run pre-pr-review first: " + why)
            head = git("rev-parse", "HEAD")
            if h["kind"] == "rebase":
                git("fetch", "-q", st["remote"], st["base"], timeout=PUSH_TIMEOUT_S)
            if h["kind"] == "rebase" and (head == h["base_head"] or run(
                    ["git", "merge-base", "--is-ancestor", "refs/remotes/%s/%s" % (st["remote"], st["base"]), head],
                    GIT_TIMEOUT_S)[0] != 0):
                raise Refused("HEAD is not rebased onto %s/%s; rebase first" % (st["remote"], st["base"]))
            remote_tip = git("ls-remote", st["remote"], "refs/heads/" + st["branch"], timeout=GH_TIMEOUT_S)
            if remote_tip.split("\t")[0] != head:  # equal: pushed before a crash lost the save
                rc, _, err = run(["git", "push", st["remote"],
                                  "--force-with-lease=refs/heads/%s:%s" % (st["branch"], h["base_head"]),
                                  "HEAD:refs/heads/%s" % st["branch"]], PUSH_TIMEOUT_S)
                if rc != 0:
                    raise Refused("push refused; no reply was posted: " + err.strip()[-500:])
            h["phase"], h["pushed"] = "pushed", head
            st["expected_head"], st["fix_rounds_used"] = head, st["fix_rounds_used"] + 1
            st["pushed"].append(head)
            log(st, "pushed", "`%s` — %s" % (head[:9], h["summary"].strip().splitlines()[0][:100]))
            save(st)
        elif h["phase"] != "pushed":
            raise Refused("handoff phase %s cannot be pushed; run apply-handoff first" % h["phase"])
        short = h["pushed"][:9]
        todo = [r for r in h["replies"] if r["to"] not in h["posted"]]
        existing = {k: comments(a.pr, k) for k in {r["kind"] for r in todo}}
        for r in todo:
            post_reply(st, r["to"], r["kind"], r["body"].replace("{commit}", short), existing[r["kind"]])
            h["posted"].append(r["to"])
            save(st)
        for login in h["reviewers"]:
            try:  # a rejected re-request (author, bot without review rights) is reported, not retried
                gh_api("repos/%s/pulls/%d/requested_reviewers" % (REPO, a.pr), "POST", {"reviewers": [login]})
            except EnvError as e:
                st["flags"].append("re-request of %s rejected: %s" % (login, e))
        st["pending_handoff"], st["status"], st["heartbeat_at"] = None, "running", 0
        st["next_poll_at"], st["idle_polls"] = 0, 0
        publish_status(st)
        save(st)
    emit({"result": "pushed", "commit": h["pushed"], "replies_posted": h["posted"],
          "fix_rounds_left": MAX_ROUNDS - st["fix_rounds_used"]})
    return 0


def cmd_resolve_handoff(a):
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        h = pending(st, ("decision", "rebase", "fix"))
        if h.get("phase") == "pushed":
            raise Refused("the fix is pushed; finish it with push-and-reply")
        # The session may have settled a head_moved decision: watch the head the PR has now.
        st["expected_head"] = gh_api("repos/%s/pulls/%d" % (REPO, a.pr))["head"]["sha"]
        st["pending_handoff"], st["status"], st["heartbeat_at"] = None, "running", 0
        log(st, "asked", "%s resolved by the session: %s" % (h["kind"], a.note))
        publish_status(st)
        save(st)
    emit({"result": "resolved"})
    return 0


def finish(st, reason):
    """Flip the run to stopped and close the status comment. Idempotent."""
    if st["status"] != "stopped":
        st["status"], st["stop_reason"], st["stopped_at"] = "stopped", reason, hhmm()
        log(st, "stopped", reason)
        publish_status(st)
    return {k: st.get(k) for k in CARRIED + ("pushed", "flags", "untrusted", "stop_reason", "pending_handoff",
                                               "acked", "inbox")}


def cmd_stop(a):
    with locked(a.pr) as (box, save):
        st = require(box, a.pr)
        phase = (st.get("pending_handoff") or {}).get("phase")
        if phase == "pushed":
            raise Refused("the fix is pushed but its replies are not; run push-and-reply first")
        if phase == "committed":
            raise Refused("the fix is committed but not pushed; run push-and-reply, or resolve-handoff "
                          "and drop the local commit first")
        summary = finish(st, a.reason)
        save(st)
    emit({"result": "stopped", "summary": summary})
    return 0


def cmd_status(a):
    with locked(a.pr) as (box, _):
        emit(require(box, a.pr))
    return 0


def main(argv):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)

    def add(name, fn, help_text):
        p = sub.add_parser(name, help=help_text)
        p.add_argument("--pr", type=int, required=True)
        p.set_defaults(fn=fn)
        return p
    add("start", cmd_start, "open or resume the run (session checkout)")
    w = add("wait", cmd_wait, "poll until an event needs the worker, the run ends, or the slice elapses")
    w.add_argument("--max-wait", type=int, default=MAX_WAIT_S)
    w.add_argument("--immediate", action="store_true")
    k = add("ack", cmd_ack, "mark inbox events handled")
    k.add_argument("keys", nargs="+")
    r = add("reply", cmd_reply, "post one non-fix reply")
    r.add_argument("--to", type=int, required=True)
    r.add_argument("--kind", choices=("inline", "issue"), required=True)
    r.add_argument("--body-file", required=True)
    r.add_argument("--ack", nargs="*")
    t = add("trigger-bits", cmd_trigger_bits, "request a fresh Bits review once per head")
    t.add_argument("--reason", required=True)
    s = add("stage-handoff", cmd_stage_handoff, "hand a fix, decision or rebase to the session")
    s.add_argument("--kind", choices=("fix", "decision", "rebase"), required=True)
    s.add_argument("--summary-file", required=True)
    s.add_argument("--message-file")
    s.add_argument("--replies-file")
    s.add_argument("--scope", nargs="*")
    s.add_argument("--reviewers", nargs="*")
    s.add_argument("--ack", nargs="*")
    add("apply-handoff", cmd_apply_handoff, "apply and commit a staged fix (session checkout)")
    add("push-and-reply", cmd_push_and_reply, "push, then post the queued replies (session checkout)")
    v = add("resolve-handoff", cmd_resolve_handoff, "drop a handoff the session settled otherwise")
    v.add_argument("--note", required=True)
    p = add("stop", cmd_stop, "stop the run")
    p.add_argument("--reason", required=True)
    add("status", cmd_status, "print the run state")
    a = ap.parse_args(argv)
    try:
        return a.fn(a)
    except Refused as e:
        emit({"result": "refused", "reason": str(e)})
        return 1
    except (EnvError, OSError, ValueError) as e:
        emit({"result": "error", "reason": str(e)})
        return 2


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
