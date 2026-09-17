---
id: find-canary-stuck-restart-wipes-frontier
type: finding
status: confirmed
depends_on: [find-canary-fixes-e-f, find-abandon-event-queue-fix]
supersedes: []
related: [find-canary-stuck-abandon-detector, find-canary-search-cannot-terminate, ev-postfixEF-onpod-live-verification, q-canary-stuck-fix-alternatives]
tags: [root-cause, referenceChains, canary, restart, frontier, no-progress-limit, NEW-THIS-SESSION]
created: 2026-08-25
updated: 2026-08-25
---

# CONFIRMED: CANARY_NO_PROGRESS_PASS_LIMIT + full frontier wipe on restart prevents ever reaching a distant-but-reachable candidate

## Reasoning chain

With Fix E/F confirmed live (starvation resolved — `runPass` went from 0 to
50 in a comparable ~40s window, see `ev-postfixEF-onpod-live-verification`),
candidates still resolve at 0/5 in every single sample. This rules out the
pain-budget/cadence gates as the (sole) explanation for zero resolution —
passes are now running continuously — and shifts the question to why a
continuously-running search still never reaches any candidate.

Live trace shows the search hits `CANARY_STUCK` abandon roughly every ~20s,
with the frontier having grown to 12,776 and then 15,699 entries at the two
observed abandon points before `restartSearch()` resets it
(`_frontier->resetForRestart()` + `_next_tag = 1`,
`referenceChains.cpp:1054-1056`). `candidate[0]`'s `klass_id` stayed at `2`
(`[B`) across the entire window (2545 matching log lines) — ruling out
candidate-list churn as a contributor.

The canary-specific stuck detector (`CANARY_NO_PROGRESS_PASS_LIMIT=30`,
hardcoded in `referenceChains.h`, see the design comment around
`:1988-1999`) fires on zero *candidate-bit* progress specifically,
independent of whether the general BFS frontier is still healthily
expanding elsewhere. Combined with `restartSearch()`'s unconditional full
wipe, this means: every search gets one shot at reaching the candidate
within roughly one cycle's worth of BFS depth (bounded by ~13-16k frontier
entries here), and if the candidate sits behind a reference chain longer
than that, no amount of wall-clock time helps — the search can never
accumulate progress across restarts.

## Evidence

- `ev-postfixEF-onpod-live-verification` — full 40s trace, `runPass done`
  frontier-size progression, two `CANARY_STUCK` abandon events at trace
  lines 143402 and 380564 in `/tmp/hotdog_trace2.log`.
- Code confirms the mechanism precisely:
  `_passes_since_last_candidate_progress` (`referenceChains.cpp:3148-3155`)
  increments on every pass where
  `_candidate_count + popcount(_candidate_found_bits)` fails to increase —
  once all 5 slots are admitted and none found, this ticks up every single
  pass regardless of `_passes_since_last_progress` (whole-graph frontier
  growth), by the design comment's own explicit intent
  (`referenceChains.h:709-725`). At `CANARY_NO_PROGRESS_PASS_LIMIT=30`
  (`referenceChains.h:1999`) this fires `CANARY_STUCK`, and
  `restartSearch()` performs a destructive full reset
  (`_frontier->resetForRestart()` + `_next_tag=1`,
  `referenceChains.cpp:1054-1056`) with zero carryover.
- **User-confirmed ground truth**: the target is a synthetic, permanently
  reachable leak (deliberately never released) — this eliminates "candidate
  is genuinely unreachable from any sampled root" as a competing
  explanation. The only remaining explanation for persistent 0/5 is that
  the algorithm cannot accumulate enough continuous BFS depth/reach in one
  ~20s/30-pass cycle to get to it, and loses all progress every cycle.

## What this rules out

- Candidate-list churn (a different `candidate[0]` offered on each restart)
  — ruled out, `klass_id=2` stable across both cycles.
- The starvation/cadence gates (`find-cpu-pain-budget-starves-canary-passes`,
  `find-threadloop-presleep-blocks-back-to-back`) as sole explanation for
  zero resolution — ruled out, they are fixed and confirmed live, yet 0/5
  persists.
- **Candidate unreachable from any sampled root** — ruled out by user
  confirmation (synthetic leak, deliberately retained, permanently
  reachable).

## Alternatives analysis

See `q-canary-stuck-fix-alternatives` for the 4 proposed fixes (C/A/B/D),
research grounding (incremental BFS, G1 SATB marking, Luby/adaptive restart
theory), and the recommendation (lean: C, the merged-stuck-detector
condition). User chose **C+B together**; implemented this session — see
`q-canary-stuck-fix-alternatives` for the code changes.

## Live-pod verification (post-deploy)

Committed+pushed as `82fec4210`. User resynced the agent on
`prof-analyzer-hotdog-jb-c944876b9-f762h` (PID 62384); confirmed via
`strings` on the loaded `.so` that `CANARY_PAIN_BUDGET_REFILL_MULTIPLIER`
and the new `_canary_stuck_restart_count`/`canaryStuckPassLimit` symbols
are present.

Two live traces (40s + 90s, 122 total `runPass done` samples,
`/tmp/hotdog_trace{3,4}.log`): **zero `CANARY_STUCK` abandons**, `searchState=0`
(RUNNING) and `abandonReason=0` (NONE) on every single pass. Frontier grew
continuously and monotonically across the whole combined window: 25,040 ->
26,626 -> 33,137 entries — no wipes, no restarts. This directly confirms
C+B fixed the destructive-restart bug: the search that previously died at
~12-16k entries every ~20s now keeps accumulating BFS reach uninterrupted
past 33k.

Candidates are still `0/5 found` in both traces — expected at this stage,
since the search was never previously allowed to run this long
uninterrupted. Whether/when it resolves is now purely a function of actual
candidate depth vs. observation time, not the restart bug. Next step: a
longer-duration trace (few minutes) to check for eventual resolution.

## Not yet done

- Longer-duration live trace to confirm eventual candidate resolution now
  that the restart-wipe bug is fixed.
