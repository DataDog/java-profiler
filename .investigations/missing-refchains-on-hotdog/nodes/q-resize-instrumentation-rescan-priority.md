---
id: q-resize-instrumentation-rescan-priority
type: question
status: open
depends_on: [find-priority-queue-starves-bfs-crawl]
related: [find-priority-queue-starves-bfs-crawl, find-holistic-design-issues]
tags: [design, rotation, growing-collections, instrumentation, NEW-THIS-SESSION]
created: 20260831
updated: 20260831
---

# User idea: bytecode instrumentation on collection resizes → rescan prioritization

The resize blindspot fix (fair-share rotation) is probabilistic: a growing
collection's new backing array is only found when the blind lap happens to
re-walk the live holder. User's idea (2026-08-31, to revisit after the
current fix lands): if we could observe collection resizes directly - e.g.
via bytecode instrumentation of the resize/mutation points
(`ArrayList.grow`, `HashMap.resize`, or more generally any "collection
mutated" event for watched classes) - we could use that as a precise signal
to prioritize re-walks of the affected holder instead of relying on
rotation luck.

## Why it fits

- The profiler already ships bytecode instrumentation machinery
  (dd-iast / dynamic instrumentation agent in the same -javaagent).
- The signal is exactly the mutation rotation exists to detect, with none
  of the false-negative geometry (dead-old-parent fanout entries, holder
  never in fanout, lap starvation).
- Cost profile: instrumentation fires only on resize of watched containers,
  not per-element mutation (a per-put signal on a hot map would be a flood);
  resizes are amortized O(1) per element, so the event rate is manageable.

## Open questions

- Which instrumentation point: `ArrayList.grow`/`HashMap.resize` only, or an
  interface-level "collection structure changed" marker on the watched
  classes' holders?
- Delivery to native: a JNI upcall into the tracker (allocation-adjacent,
  not signal context) - or a flag on the frontier entry checked by the next
  rotation pass.
- Cross-JVM: J9/Zing instrumentation parity.
- Whether the existing fair-share rotation (once verified) is good enough
  that the added machinery isn't justified - the pod evidence (leak_parents
  19k, mostly dead) suggested fanout was heavily polluted, so a precise
  signal could replace the fanout tier entirely rather than complement it.

Parked until the rotation fair-share fix + correlation scenario are verified.
