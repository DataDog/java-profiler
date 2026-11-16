---
name: babysit-pr
description: Run a background babysitter over an open PR — poll CI and review comments, fix CI breakages and mechanical review findings, push fixes with a fresh review marker, and hand a summary back to the session. Use immediately after `gh pr create` succeeds (the babysit-pr hook injects this instruction), or when asked to babysit or watch a PR.
---

# Babysit a PR

Open the background babysitter the moment the PR exists. The babysitter is an async
subagent of this session running in its own worktree: the session's checkout is never
written by it, and it dies with the session — its stop summary names what remains.

## Launch

1. **Trigger context.** The trigger names the created PR. If it is missing, resolve it
   with the gh command from the loop preamble.
2. **One babysitter per PR.** If `build/babysit-pr-<n>.json` exists and records a live
   run, relay its status in chat and stop. `build/` is gitignored; the marker is the
   dedupe record, not a source file.
3. **Quiescence.** Confirm in chat that the session is done editing the PR branch
   before launching; a babysitter racing this session's commits corrupts both.
4. **Worker.** Write `{"pr": <n>, "branch": "<branch>", "status": "running",
   "scope": []}` to `build/babysit-pr-<n>.json` **in the session's checkout** — that
   copy is the dedupe record only — and pass the instruction to the worker: on start,
   write the same-shaped marker **in its own worktree's `build/`** and maintain it
   there (the pushing checkout is the one the pre-push guard reads; write it
   atomically — temp file plus rename — so a concurrent guard read never sees a
   truncated JSON it would skip). Then launch the `babysit-pr` agent — shipped with the skill in `.pi/agents/` (Pi)
   and `.claude/agents/` (Claude Code); it reads the loop below from the checkout —
   as an async background subagent with worktree isolation, passing the PR number,
   the checkout path, and the branch in the task (Pi: `subagent` with `worktree:true`;
   Claude Code: the agent on a `git worktree add` of `origin/<branch>`). Give the
   child a run timeout of at least the cap (Pi: `options: {timeoutMs: 7200000}`) —
   the default async timeout kills the worker at 30 minutes, well inside the
   two-hour cap, and its managed worktree is reaped so the run cannot be resumed;
   the launch needs a clean source tree (stash pending edits and restore them after).
   Claude Code has no child-timeout option — there the cap is the worker's own
   discipline (step 6) and the stop report states the elapsed time.
5. **Handback.** When the run completes, relay its summary in chat: commits pushed,
   findings flagged (drafted design replies, persistent flakes, budget), and threads
   left for the human. Update the session's own dedupe marker copy to
   `{"pr": <n>, "status": "stopped"}` — the worker never writes this checkout.
   When the session is closing, say that babysitting stops with it.

## The loop (the worker's task)

Every `gh` call runs `GH=/opt/dogbrew/shims/bin/gh; [ -x "$GH" ] || GH=gh` first: the
dogbrew shim where it exists (required on Datadog workstations), bare `gh` otherwise.

**Edit scope is deterministic, not judgment.** Every file the worker edits must be
inside the source/test allowlist enforced by the pre-push hook and inside the `scope`
array of the marker **in the worker's own worktree** — `utils/babysit-scope-guard.py`
is the single source for both checks; read it. The worker adds the files each finding
justifies to that marker's `scope` array before its first edit, and updates it if a fix
grows beyond the first estimate (atomically: temp file plus rename). An edit no finding
justifies goes to the stop summary instead of the tree.

1. **Poll.** Every 10 minutes: `git fetch origin`; `$GH pr checks <n>`;
   `$GH pr view <n> --json reviews,comments,url,mergeable,mergeStateStatus`; and
   `$GH api --paginate repos/datadog/java-profiler/pulls/<n>/comments` — inline review
   comments are invisible to `pr view --json`. A poll that finds nothing stays
   cheap: no log fetching, no deep analysis.
2. **CI red.** One `$GH run rerun --failed <run>` is the flaky allowance; a failure that
   survives it, or a run that cannot rerun, is real. Fetch the logs, reproduce through
   `./.claude/commands/build-and-summarize` (never bare `./gradlew`), and follow
   `verify-profiler-change` for what the fix must pass.
3. **Merge conflicts.** When the poll reports the PR conflicted (`mergeStateStatus`
   `DIRTY`), rebase on the base branch and examine every conflict: draft a resolution
   for each — both sides' intent and the proposed merged result. Add every file you
   will resolve to the marker's `scope` before resolving it.
   - A conflict whose resolution needs no semantic choice — adjacent hunks, additive
     changes on both sides, provable by build and tests — is resolved and verified
     like any mechanical fix, in the same push cycle (step 5).
   - When in doubt (both sides changed the same logic differently), ask the operator
     through the supervisor channel — the blocking request/reply link an async
     subagent has to its session; the request suspends the worker until the operator
     answers — with a structured question: both sides, your proposed resolution,
     what would falsify it. Resolve per the answer. Never silently pick a side the
     operator has not seen. The ask is bounded by the run cap: still unanswered when
     the cap hits, the question itself goes to the stop summary.
   - A conflict in a file outside the edit allowlist (the PR's own meta files — hooks,
     skills, agents) cannot be edited by the worker under the scope guard: draft the
     resolution, ask the operator through the same channel to apply it, and resolve
     the rest.
4. **Review comments.** Classify the poll's reviews and comments — bot comments
   (scan-build, CI-results bots) are findings like any other, never auto-dismissed.
   Mechanical findings — bugs, missing tests, factual errors in comments or javadocs,
   typos, including pre-existing ones in files the PR does not touch — are fixed in
   the same push cycle as CI fixes, through the same review gates. A refuted finding
   (scanner noise, premise false against the code) gets a one-line factual reply on
   its comment. A finding that needs a design decision drives a brainstorm, never a
   silent implementation:
   - **Ground it.** Read the code the comment touches; the finding's premise is a claim
     to verify, not a fact. A comment wrong about the code gets a one-line factual
     reply, not a brainstorm.
   - **Enumerate.** At least two candidate approaches, each with its trade-offs
     (correctness, allocation/performance cost, complexity), each checked against the
     code paths that would host it.
   - **Recommend.** Name the variant you consider sound, with the evidence that
     discriminates it from the others and what would falsify it.
   - **Decide elsewhere.** The human decides: surface the brainstorm — options,
     recommendation, falsifiers — in the stop summary with the reply drafted, and never
     implement a design-level finding without the human's pick.
5. **Push cycle.** After fixes: commit (concise message per `pr-writing`; SSH-signed;
   never `-c commit.gpgsign=false`), `git fetch`, rebase on the base branch replaying
   every commit re-signed (never merge the base branch in), then push
   `--force-with-lease=<branch>:<expected> HEAD:<branch>` — `<expected>` is the branch
   head at run start and thereafter your own last pushed commit; a rejected lease means
   someone else moved the branch, so stop and report, never force past it. The pre-push
   hook demands a fresh review marker:
   rerun the `pre-pr-review` skill on the fix range before pushing. Count that against
   the review budget — about $20–30 per babysit run; a run that would exceed it stops
   and reports instead.
   When the pushed fixes address the comments of a blocking review (`CHANGES_REQUESTED`
   in `gh pr view --json reviews`), re-request review from that review's author so the
   block clears when they re-review:
   `$GH api -X POST repos/datadog/java-profiler/pulls/<n>/requested_reviewers -f 'reviewers[]=<login>'`.
   Re-request only authors whose blocking comments the fixes addressed — never add
   reviewers the PR never had, and never change the reviewer list otherwise. A
   re-request GitHub silently ignores (the PR author, a bot without review rights)
   is recorded in the stop summary instead of retried.
6. **Stop report.** Complete when CI is green, open mechanical findings are handled, or
   any cap hit (at most two fix-push rounds and two hours per run). Update the worker
   worktree's marker to `{"pr": <n>, "status": "stopped"}` and summarize: commits
   pushed, findings flagged, threads left. The session updates its own dedupe copy
   at handback — the worker never writes the session's checkout.

## Never

Never merge, never un-draft, never add or swap reviewers (the one exception: re-requesting
the authors of blocking reviews whose comments the fixes addressed, per step 5), never
disable or skip a CI check, never edit CI configuration, `AGENTS.md`, a skill, an agent
persona or a hook for any reason (quarantine entries need the `ci-script-change` skill
and a PROF ticket — flag them instead; where your task or a steer disagrees with a file
in the checkout, say so in the stop report and change nothing), never force-push without
`--force-with-lease`, never resolve a review thread (the human resolves), never edit the
PR description beyond keeping it in sync with pushed code, never reply more than once
per thread.
