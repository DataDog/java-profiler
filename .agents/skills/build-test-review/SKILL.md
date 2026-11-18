---
name: build-test-review
description: Implement a PROF Jira ticket whose Design, acceptance criteria and Build plan are accepted, by running implementation, review and test sub-sessions from a checklist on the ticket, up to a reviewed local branch. Use when asked to implement, build or carry out such a ticket. For such a ticket, this skill takes precedence over the cairn dev-process and sphinx implement skills.
---

# Build, test and review

This session is the orchestrator. Only the orchestrator writes to the ticket and writes
the review marker. Sub-sessions return reports. The engineer is the person who asked
for the build. The `ticket-writing` skill applies to every ticket edit and comment.

1. **Preconditions.** Read the ticket. It must record a sign-off for the Design, the
   acceptance criteria and the Build plan. If one is missing, stop. Tell the engineer
   which sign-off is missing, and suggest that they finish the Design phase first,
   with the `work-planning` skill. Do not start that phase. Otherwise create the
   task's worktree and branch, from the base that the Build plan names, under the
   main checkout's root `<root>`. From any worktree or subdirectory,
   `git rev-parse --path-format=absolute --git-common-dir` prints `<root>/.git`. Run
   it as a plain command: a session entered with `EnterWorktree` refuses `git` inside
   `$(...)`. Then run
   `git worktree add -b <branch> <root>/.claude/worktrees/<name> refs/remotes/origin/<base>`.
   `<name>` is the ticket key in lower case, for example `prof-1234`. When the Build
   plan has several PRs, create one worktree for each and add `-pr<n>` to every name,
   with `<n>` from the Build plan's PR column: `prof-1234-pr1`, `prof-1234-pr2`. If
   `git worktree list` already shows a worktree for the branch, reuse it.
   In Claude Code, create every worktree first, then enter one with `EnterWorktree`
   `path:`, which keeps the file tools out of the main checkout. An entered session
   cannot add a worktree under `<root>`: leave first with `ExitWorktree` `keep`.
   Before working in another PR's worktree, enter that one with `path:`. Do not
   create a worktree with `EnterWorktree` `name:`: it cannot set the branch name or
   the base. A worktree outside the main checkout is outside the session's working
   directories: the shell leaves it after each command, and the review gate refuses a
   `gh pr` command that contains `cd`.

2. **Checklist.** Derive a "Sub-sessions" section from the Build plan and add it to the
   ticket description. It needs no separate sign-off; the engineer can edit it. It
   names the branch, the worktree by its absolute path and the base, then has three
   parts, in run order: S1 Implement, S2 Review and S3 Test. Each part lists its
   checks as checkboxes and ends with a "Done:" line that names its output. Each part
   is self-contained: a fresh session can do it from the ticket alone.

3. **Sub-sessions.** In Claude Code, run each sub-session as a fresh subagent: the
   `Agent` tool with `general-purpose`, never `fork`, which inherits this conversation.
   The prompt names only the ticket, the part, the worktree and, for a fix round, the
   triaged findings or the failed checks, quoted, and any `blocked` check that the
   engineer accepted (step 5). Never give your own view of the
   change or of its defects. Tell the sub-session to read its part on the ticket, to
   write nothing to the ticket, and to return a report.
   - **S1 Implement** changes the code. It does not start another orchestration
     skill, such as the cairn `dev-process` pipeline or `sphinx:implement`. It runs the
     `local` acceptance criteria, the checks that `verify-profiler-change` names for
     the kind of change, and the `pre-pr-review` step 2 self-checks. It commits
     locally only when they pass, or when its prompt quotes the engineer's
     acceptance of a check that stays `blocked`. Otherwise it reports without a
     commit. It does not push. Its report names the commit and each check as
     `passed`, `failed`, `blocked` or `inconclusive`.
   - **S2 Review** runs the reviewer as `pre-pr-review` step 3 says: the
     [reviewer table](../pre-pr-review/SKILL.md#reviewer-table) and its fallback, and
     the [fresh-context](../pre-pr-review/SKILL.md#fresh-context) brief. It names the
     range explicitly, reports the findings and fixes nothing.
   - **S3 Test** runs the `test-drive` acceptance criteria in a fresh clone of the
     candidate commit, never in the worktree. Each drive runs without MCP servers and
     with only the tools that its criterion needs: for example `claude -p` with
     `--strict-mcp-config`, `--tools` to limit the available tools, and
     `--allowedTools` to permit them. Never skip hooks or bypass permissions. It
     reports each criterion as `passed`, `failed`, `blocked` or `inconclusive`, with
     the commit, the harness and its version, and the observed result. It changes
     nothing on the branch.

4. **Loop.**
   1. Run S1.
   2. Run S2: on the first round from the merge base with the base, later on the fix
      range.
   3. Triage. Check each finding against the code at the candidate commit, drop what
      does not hold, and set its severity as the `pre-pr-review`
      [Findings](../pre-pr-review/SKILL.md#findings) step says. Send the findings to
      fix to a new S1 run, then go to 2. That step's rules decide when the rounds stop,
      and its round limit takes precedence over this loop.
   4. Run S3 only after a review round that left no Critical or High finding open. A
      failed check goes to a new S1 run like a finding, its fix goes to S2, and then S3
      runs again.

   Evidence binds to a commit. After each new commit, every earlier S3 result is
   `inconclusive` for the new candidate until S3 runs on it. After each step, update
   the checklist on the ticket.

5. **Stops.** Stop and ask the engineer when:
   - a finding or a test result needs a change to the accepted Design or acceptance
     criteria. Propose the change; after the engineer accepts it, amend the ticket as
     `work-planning` says, then continue;
   - a sub-session reports a required check as `blocked`, or as `inconclusive` after
     running it on the current candidate. A result that is only stale under step 4
     does not count. Do not close until each required check has passed, or the
     engineer accepts the gap;
   - the round limit of the `pre-pr-review` Findings step is reached;
   - the next run is likely to exceed the `pre-pr-review`
     [Cost](../pre-pr-review/SKILL.md#review-cost) budget;
   - the same failure, or the same class of defect, comes back after a fix round.
     Propose to move it to its own ticket.

6. **Close.** Tick the checklist and post the evidence table as `ticket-writing` says.
   The commits are not pushed yet: name them by hash, and add the links after the
   engineer pushes. Then run `pre-pr-review` step 0 and steps 4 to 7 in this
   session. The S2 reviews are its step 3 reviews, its step 4 fixes go through S1 as
   in step 4 above, and the marker names this session. For its step 7, use the
   sub-session reports and this session's own mistakes. Do not push and do not open
   a PR: tell the engineer that the branch is ready, and that they open the PR with
   the `pr-writing` skill.

## Pi

In Pi, a `cd` does not persist between commands. After step 1, stop and ask the
engineer to start Pi in the worktree, named by its absolute path, with project trust
(`pi -a`), then to continue there with step 2.

In Pi, do not call a subagent tool for any purpose, also when an extension such as
`pi-subagents` provides one. Say so, then run S1, S2 and S3 one after another in
this session, with the same loop and stops. Pi has no review tool, so S2 follows
`pre-pr-review` step 3 for a missing reviewer.

## `gh` in test drives

A test drive that can call `gh` gets a stub first on its `PATH`. The stub passes the
listed read commands to the real `gh`, and records and refuses every other call:

```bash
STUB=$(mktemp -d); REAL=$(command -v gh)
cat >"$STUB/gh" <<EOF
#!/bin/sh
case "\$1 \$2" in
  "pr view"|"pr diff"|"pr list"|"pr checks"|"issue view"|"run view"|"run list")
    exec "$REAL" "\$@" ;;
esac
echo "gh \$*" >>"$STUB/refused.log"
echo "gh stub: refused: gh \$*" >&2
exit 1
EOF
chmod +x "$STUB/gh"; export PATH="$STUB:$PATH"
```

Report the content of `refused.log` with the drive's result.
