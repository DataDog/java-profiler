# Copyright 2026, Datadog, Inc.
"""Pure policy core of the babysit-pr CLI (utils/babysit-pr.py): no I/O.

CI rollup dedupe, the comment trust gate, the thread census, the per-poll decision
(which mechanical actions run in Python and which events wake the LLM worker) and the
status-comment rendering. The CLI fetches every input, calls these functions, and
performs the returned actions.
"""

import re

SIGNATURE = "<!-- babysit-pr v1 -->"
BITS_CONTEXT = "bits-review/head"
BITS_TRIGGER = "@datadog review"
# Pinned review bots trusted by login (trailing [bot] stripped) besides the Bits gate's
# id allowlist; a login match counts only for user.type == "Bot", so a human account
# registered under one of these names is rejected.
PINNED_BOT_LOGINS = frozenset({"dd-octo-sts", "chatgpt-codex-connector", "scan-build"})
TRUSTED_PERMISSIONS = frozenset({"admin", "maintain", "write"})
GHA_RUN = re.compile(r"/actions/runs/(\d+)(?:/|$)")
TRUSTED_IDS_LITERAL = re.compile(r"TRUSTED_BOT_IDS\s*=\s*frozenset\(\s*\{([^}]*)\}", re.S)

POLL_S = 600
IDLE_POLL_S = 1200
# Polls without any new fact before the interval backs off to IDLE_POLL_S.
IDLE_AFTER = 3
# Run-log entries rendered into the status comment; bounds the body below GitHub's
# 65536-character comment limit however long the run log grows.
LOG_ENTRIES = 50


def parse_trusted_bot_ids(source):
    """The TRUSTED_BOT_IDS set from bits_review_gate_policy.py source text, or an empty
    set when the literal is absent (an empty set trusts no bot by id)."""
    m = TRUSTED_IDS_LITERAL.search(source or "")
    return frozenset(int(x) for x in re.findall(r"\d+", m.group(1))) if m else frozenset()


def dedupe_checks(check_runs):
    """{name: run} keeping, per name, an in-flight run over every completed one (a
    pending rerun must never let a stale result drive a verdict), then the newest
    started_at among the remaining candidates; on a tie the earlier entry stays."""
    best = {}
    for run in check_runs:
        name = run.get("name")
        cur = best.get(name)
        if cur is None:
            best[name] = run
            continue
        rank = (run.get("status") != "completed", run.get("started_at") or "")
        if rank > (cur.get("status") != "completed", cur.get("started_at") or ""):
            best[name] = run
    return best


def ci_summary(check_runs, statuses):
    """{"state": green|red|pending, "failing": [...], "pending": [...]} over deduped check
    runs and commit-status contexts, excluding the Bits context (reported separately).
    A failing entry carries name, kind (gha|gitlab|other), run_id (gha only) and url."""
    failing, pending = [], []
    for name, run in sorted(dedupe_checks(check_runs).items()):
        if run.get("status") != "completed":
            pending.append(name)
        elif run.get("conclusion") not in ("success", "neutral", "skipped"):
            url = run.get("details_url") or ""
            m = GHA_RUN.search(url) if "github.com" in url else None
            failing.append({"name": name, "kind": "gha" if m else "other",
                            "run_id": int(m.group(1)) if m else None, "url": url})
    latest = {}
    for st in sorted(statuses, key=lambda x: x.get("updated_at") or "", reverse=True):
        latest.setdefault(st.get("context"), st)  # newest update per context; stable on ties
    for ctx, st in sorted(latest.items()):
        if ctx == BITS_CONTEXT:
            continue
        if st.get("state") == "pending":
            pending.append(ctx)
        elif st.get("state") != "success":
            failing.append({"name": ctx, "kind": "gitlab" if ctx.startswith("dd-gitlab/") else "other",
                            "run_id": None, "url": st.get("target_url") or ""})
    state = "red" if failing else "pending" if pending else "green"
    return {"state": state, "failing": failing, "pending": pending}


def bits_state(statuses):
    """success|failure|pending|missing for the newest bits-review/head status."""
    for st in sorted(statuses, key=lambda x: x.get("updated_at") or "", reverse=True):
        if st.get("context") == BITS_CONTEXT:
            s = st.get("state")
            return "failure" if s in ("failure", "error") else s
    return "missing"


def trust_of(user, pr_author, permission, trusted_ids):
    """True when the author may steer the babysitter: the PR author, a collaborator with
    admin/maintain/write (permission is the looked-up role or None), or a Bot by
    allowlisted id or pinned login."""
    if not isinstance(user, dict):
        return False
    login = user.get("login") or ""
    if user.get("type") == "Bot":
        return user.get("id") in trusted_ids or re.sub(r"\[bot\]$", "", login) in PINNED_BOT_LOGINS
    return login == pr_author or permission in TRUSTED_PERMISSIONS


def is_own(comment, self_id):
    """A comment posted by the babysitter: the signature AND the babysitter's account id
    (the author shares the account, so the id alone cannot tell them apart)."""
    return (comment.get("user") or {}).get("id") == self_id and \
        (comment.get("body") or "").rstrip().endswith(SIGNATURE)


def census(inline_comments, replied, self_id):
    """{root_id: {"root": comment, "answered": bool}} for every inline thread. A thread is
    answered when its root id is in replied or a reply in it is the babysitter's own."""
    threads = {}
    for c in inline_comments:
        if not c.get("in_reply_to_id"):
            threads[c["id"]] = {"root": c, "answered": c["id"] in replied}
    for c in inline_comments:
        root = c.get("in_reply_to_id")
        if root in threads and is_own(c, self_id):
            threads[root]["answered"] = True
    return threads


def _event(kind, key, **facts):
    return dict(kind=kind, key=key, **facts)


def decide(state, snap, trusted, now):
    """The poll decision. Returns {"outcome", "actions", "events", "facts", "untrusted"}.

    outcome: stop (PR closed/merged or cap hit; facts["reason"]), green_done,
    action_needed (events wake the LLM), continue. actions are mechanical steps the CLI
    runs without waking the LLM: ("rerun", run_id) once per GHA run and
    ("trigger_bits", head) once per head. An event is surfaced once (state["surfaced"]),
    so a finding the worker chose not to act on does not re-wake it every poll.
    trusted(user) answers the trust gate."""
    pr, head = snap["pr"], snap["pr"]["head"]
    out = {"outcome": "continue", "actions": [], "events": [], "facts": {}, "untrusted": []}
    if pr["state"] != "open":
        out["outcome"], out["facts"]["reason"] = "stop", "PR merged" if pr.get("merged") else "PR closed"
        return out
    if now >= state["deadline_at"]:
        out["outcome"], out["facts"]["reason"] = "stop", "two-hour cap reached"
        return out
    ci = ci_summary(snap["check_runs"], snap["statuses"])
    bits = bits_state(snap["statuses"])
    out["facts"].update(ci=ci["state"], bits=bits, head=head)
    surfaced = set(state["surfaced"])
    events = []

    def surface(ev):
        if ev["key"] not in surfaced:
            events.append(ev)

    if head != state["expected_head"]:
        surface(_event("head_moved", "head:" + head, head=head, expected=state["expected_head"]))
    if pr.get("mergeable_state") == "dirty":
        surface(_event("conflict", "conflict:" + head, head=head))
    for f in ci["failing"]:
        if f["kind"] == "gha" and f["run_id"] not in state["retried_runs"]:
            out["actions"].append(("rerun", f["run_id"], f["name"]))
        else:
            surface(_event("ci_red", "ci:%s@%s" % (f["name"], head), check=f["name"], ci_kind=f["kind"],
                           run_id=f["run_id"], url=f["url"]))
    if bits == "failure":
        surface(_event("bits_red", "bits:" + head, head=head))
    elif bits in ("pending", "missing") and (ci["state"] == "green" or pr.get("draft")) \
            and head not in state["bits_triggered"]:
        out["actions"].append(("trigger_bits", head))

    self_id = state.get("self_id")
    threads = census(snap["inline_comments"], set(state["replied"]), self_id)
    open_threads = 0
    for tid, t in sorted(threads.items()):
        if t["answered"] or is_own(t["root"], self_id):
            continue
        if not trusted(t["root"].get("user")):
            out["untrusted"].append(_brief(t["root"]))
            continue
        open_threads += 1
        surface(_event("thread", "thread:%d" % tid, **_brief(t["root"])))
    for r in snap["reviews"]:
        if (r.get("body") or r.get("state") == "CHANGES_REQUESTED") and not is_own(r, self_id) \
                and r["id"] not in state["replied"]:
            if trusted(r.get("user")):
                surface(_event("review", "review:%d" % r["id"], state=r.get("state"), **_brief(r)))
            else:
                out["untrusted"].append(_brief(r))
    for c in snap["issue_comments"]:
        body = (c.get("body") or "").strip()
        if is_own(c, self_id) or body == BITS_TRIGGER or c["id"] in state["replied"]:
            continue
        if trusted(c.get("user")):
            surface(_event("comment", "comment:%d" % c["id"], **_brief(c)))
        else:
            out["untrusted"].append(_brief(c))

    out["facts"]["open_threads"] = open_threads
    out["events"] = events
    if events:
        out["outcome"] = "action_needed"
    elif ci["state"] == "green" and bits == "success" and open_threads == 0 \
            and pr.get("mergeable_state") != "dirty" and head == state["expected_head"]:
        out["outcome"] = "green_done"
    return out


def _brief(c):
    user = (c.get("user") or {}).get("login")
    body = re.sub(r"\s+", " ", c.get("body") or "")[:200]
    brief = {"id": c["id"], "author": user, "gist": body}
    if c.get("path"):
        brief.update(path=c["path"], line=c.get("line") or c.get("original_line"))
    return brief


def next_interval(idle_polls):
    return IDLE_POLL_S if idle_polls >= IDLE_AFTER else POLL_S


def render_status(state, now_hhmm):
    """The single status comment: visible line, collapsed run log, italic footer."""
    entries = state["run_log"][-LOG_ENTRIES:]
    log = "\n".join("- **%s** · %s · %s" % (e["t"], e["tag"], e["fact"]) for e in entries)
    if len(state["run_log"]) > LOG_ENTRIES:
        log = "- … %d earlier entries\n%s" % (len(state["run_log"]) - LOG_ENTRIES, log)
    f = state.get("facts") or {}
    if state["status"] == "stopped":
        footer = "✅ *stopped %s UTC · %s*" % (state.get("stopped_at", now_hhmm), state.get("stop_reason", ""))
    else:
        footer = "👀 *watching · since %s UTC · CI %s · %d findings answered · Bits %s*" % (
            state["started_hhmm"], f.get("ci", "unknown"), len(state["replied"]), f.get("bits", "unknown"))
    return ("🐶 **babysit-pr** is watching this PR — CI breakages and mechanical findings are "
            "fixed and pushed automatically; design decisions are always brought to you.\n\n"
            "<details><summary>This run</summary>\n\n%s\n\n</details>\n\n%s\n\n%s"
            % (log, footer, SIGNATURE))
