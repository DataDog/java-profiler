# Find: anchor-selection tail starvation (root cause of zero ReferenceChain events)

## What was found (round 13, probe-verified)

The LEAK_BUFFER wrapper is admitted root-attached STATIC_FIELD correctly,
but the static-anchor collector can never reach it:

- Anchor index ≈ 28k entries (the sweep admits ~0.83 statics per loaded
  class; 34.3k classes on this JVM, nearly all non-bootstrap — app-priority
  or per-holder-class cohorting do NOT shrink the set meaningfully here).
- Selection iterates in admission order (= sweep class-array order), 16
  collector + 16 FIFO per pass, avg 81 edges per anchor walk vs the 3741
  edge pass budget → the walk budget is saturated at ~32-46/pass.
- Search lifetime ≈ 190 passes (frontier 0→250k cap at 1.3-2k inserts/pass).
  Coverage per search ≈ 4k of 28k (14%), always from index position 0
  (cursor reset by restartSearch — the index itself is cleared, so there is
  nothing to resume from).
- The wrapper is admitted at sweep cursor 25301/34310 (75%) → index position
  12-21k → deterministically out of reach, every search, forever.

Fix B+C (budget 4→16/32, leak_tag priority, O(index) iteration) fixed the
walk RATE but could not fix the ORDER: the wrapper's entry has leak_tag=0
(the [B chunks carry the leak tags), so the leak-priority sort does not
promote it.

## Why the leak-side machinery cannot rescue it

The leak chunks are only reachable THROUGH the wrapper's subtree (static →
wrapper → ArrayList → elementData → chunks). No walk reaches them, so:
- zero `leak-tag intercepted` conversions,
- `_leak_parent_fanout` is seeded only from ordinary root-reachable [B
  entries (seedLeakAccumulationForNewlyWatchedKlass scans existing frontier
  entries) → fanout=1 noise; the wrapper/elementData never attributed,
- BFS expansion of the wrapper is equally tail-starved (pendingExpand FIFO
  is 148k deep when the wrapper is admitted mid-search).

Corollary bug found: restartSearch() does not clear
_candidate_discovered_tags (frontier tags) → stale tags resolve into
zeroed/new-search slots → pollWatchedTargets reconstructChain failures;
when the slot holds a live new-search entry this can emit a chain event for
the WRONG object (the likely origin of the earlier "noise [B instance"
event). Clear discovered tags on restart.

## Fix options (presented to user, decision pending)

A. Class-shape priority: exclude leaf-class anchors from the index
   (String/Class/boxed/primitive arrays — fixed well-known list, resolvable
   without interface walks) and/or prioritize collection-shaped holders.
   Wrinkle: shape resolution cannot run inside heap callbacks (no JNI) —
   needs a lazy per-class shape cache filled outside callbacks.
B. Cross-restart coverage rotation (persist a selection start fraction) +
   budget tuning (measured: ~46/pass ceiling from 81-edge avg walk cost).
   Slow convergence: 6-14 search lifetimes (hours) for full coverage.
C. One-shot unrestricted whole-heap FollowReferences at search start —
   admits the whole graph including static subtrees, firing leak-tag
   interception everywhere in one bounded STW; costs seconds of STW once
   per search and must contend with the 250k frontier cap.
D. A+B combined.

## Lessons

- The "budget-4 lottery" framing (round 10-11) was wrong in an important
  way: the selection ORDER is admission order, and admission order follows
  the sweep's class-array order. Any fix that only changes RATE leaves the
  holder's position unchanged. Rate × lifetime ≥ index size is the
  invariant that must hold for coverage; measure all three before assuming
  a rate fix is enough.
- Ground-truth probes (JNI reads of the actual app object) resolve
  contradictory deduction chains in one redeploy; prefer them over
  enumerating every possible admission shape.
