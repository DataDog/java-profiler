# StringDictionary Concurrency Model

## Overview

`StringDictionary` is a triple-buffered, lock-free string-to-integer dictionary used to
assign stable JFR constant-pool IDs to class names, endpoint labels, and context values.
Three instances live in `Profiler`: `_class_map`, `_string_label_map`, and
`_context_value_map`.

Its concurrency model has two orthogonal mechanisms that address two distinct problems:

| Mechanism | Problem solved |
|-----------|---------------|
| `_accepting` + `RefCountGuard` | Buffer reset safety: no reader is mid-table when `clearAll()` zeroes the root slots |
| `SignalBlocker` | Rotation window safety: no profiling signal fires on the dump thread between Phase 1 and Phase 2 of `rotate()` |

These are independent. Neither implies the other.

### Key string ownership — the arena

Each `StringDictionaryBuffer` owns a `StringArena`: a lock-free bump allocator backed by a
single `malloc`'d block. All key strings are allocated from this arena instead of
individual `malloc` calls. Overflow `SBTable` chain nodes remain heap-allocated.

Consequences:

- **`clear()` is O(number-of-overflow-nodes)** rather than O(number-of-entries). The arena
  is reset with a single atomic store; no per-key `free()` is needed.
- **The TOCTOU gap between the `_accepting` acquire-load and `RefCountGuard::count++` is
  benign.** Even if `clearAll()`'s drain misses a racing caller on a weakly-ordered CPU,
  that caller reads from the memset-zeroed root table and returns 0 — the arena memory
  is still valid, just logically reclaimed. No UAF is possible. The seq_cst recheck
  that previously closed this window has therefore been removed from the hot path.
- **Arena capacity is sized per dictionary** (configured in `Profiler`):
  `_class_map` 4 MB per buffer (class names accumulate across rotations);
  `_string_label_map` and `_context_value_map` 512 KB per buffer (bounded by `size_limit`).
  On exhaustion `insert_with_id` returns 0, the same behaviour as a `malloc` failure.

---

## Buffer Roles

The three backing buffers (`_a`, `_b`, `_c`) cycle through three roles:

```
         ┌───────────┐   ┌───────────┐   ┌───────────┐
         │  ACTIVE   │   │   DUMP    │   │  SCRATCH  │
         │           │   │           │   │           │
Writes → │ new IDs   │   │ stable    │   │ two       │
         │ from all  │   │ snapshot  │   │ rotations │
         │ callers   │   │ for JFR   │   │ behind    │
         └───────────┘   └───────────┘   └───────────┘
              ↑ rotate()       ↑               ↑
         becomes DUMP    becomes SCRATCH  becomes ACTIVE
```

`_rot.active()` — current write target  
`_rot.dumpBuffer()` — the buffer handed to `writeCpool()` after `rotate()`  
`_rot.clearTarget()` — the scratch buffer (two rotations behind)

---

## Caller Map

Different callers reach the dictionary under different locking contexts:

```
                        ┌────────────────────────────────────────┐
                        │           StringDictionary             │
                        │                                        │
  Signal handler ───────┼──→ bounded_lookup(key, len)           │
  (SIGPROF/SIGVTALRM)   │    read-only, signal-safe              │
                        │                                        │
  JNI: recordTrace0 ────┼──→ bounded_lookup(key, len, limit)    │
  JNI: registerConst0 ──┼──→ bounded_lookup(key, len, limit)    │
  (no shard lock held)  │    insert-capable, NOT signal-safe     │
                        │                                        │
  JNI: lookupClass ─────┼──→ lookup(key, len)                   │
  (no shard lock held)  │    insert + malloc, NOT signal-safe    │
                        │                                        │
  Dump thread ──────────┼──→ lookupDuringDump(key, len)         │
  (inside jfr_op,       │    reads dump then active; may insert  │
   lockAll() held)      │    NOT signal-safe, single-threaded    │
                        │                                        │
  Profiler::start() ────┼──→ clearAll()                         │
  (no lock held)        │    resets all three buffers            │
                        └────────────────────────────────────────┘
```

**Key point**: `lockAll()` gates `CallTraceStorage` writers, not dictionary writers.
`recordTrace0` and `registerConstant0` reach `bounded_lookup` before any shard lock
(`_locks[]`) is acquired. `lookupDuringDump` runs inside `jfr_op()` which is called
while `lockAll()` is held, but only because the dump as a whole needs that exclusion —
the dictionary itself does not require it.

---

## RefCountGuard Protocol

Every `lookup` / `bounded_lookup` call that intends to read or write the active buffer
wraps the access in a `RefCountGuard`:

```
Caller                        clearAll() / rotate()
──────                        ─────────────────────

1. load _accepting (acquire)
   → false? return 0

2. active = _rot.active()

3. RefCountGuard guard(active)
   → store active_ptr (release)
   → count++ (release)          ← scanner sees this

4. guard.isActive()? → probe
   slot failure? return 0

5. _rot.active() == active?
   → changed? continue loop

6. ... read/write buffer ...

7. ~RefCountGuard()
   → count-- (release)
   → clear active_ptr (release)

                              waitForAllRefCountsToClear():
                              scan all slots; block until
                              every count == 0 or active_ptr
                              does not match target buffer

                              → then arena.reset() + memset root table
```

### Why there is no seq_cst recheck

On weakly-ordered CPUs (ARM64) there is a TOCTOU window between step 1 and step 3:

```
Thread A (caller)          Thread B (clearAll)
─────────────────          ───────────────────
load _accepting → true     (not yet)
active = _rot.active()
                           _accepting.store(false, seq_cst)
                           waitForAllRefCountsToClear()
                           → sees count = 0 for A (count++ not yet visible)
                           → returns
                           arena.reset() + memset root table
RefCountGuard guard(...)
count++ (release)
active->lookup(...)
  → reads zeroed root table slot → null key → returns 0
```

With the arena, Thread A's read after the memset lands on the zeroed root table and
returns 0 — no UAF because the arena memory is still physically valid. A seq_cst
recheck after step 3 would close the window more tightly (guaranteeing the drain sees
the guard), but at the cost of a barrier on every signal-handler lookup. Since
`clearAll()` is called only at profiler restart (virtually never in production), the
benign-miss trade-off is correct: the recheck was removed.

---

## clearAll() Protocol

```
clearAll()
  1. _accepting.store(false, seq_cst)
       ↳ subsequent lookup() / bounded_lookup() callers fail their
         _accepting acquire-load and return 0 immediately
  2. RefCountGuard::waitForAllRefCountsToClear()
       ↳ drains every caller already past the _accepting load.  The
         drain is best-effort: a racing caller may slip through, but
         it then reads from the memset-zeroed root table (step 3) and
         returns 0 — no UAF because the arena memory is still valid
         (see "Why there is no seq_cst recheck" above).
  3. _a.clear(); _b.clear(); _c.clear()
       ↳ freeTable() on each buffer — safe because no guard is live
  4. _rot.reset()
  5. _next_id.store(1, relaxed)
  6. reset counters
  7. _accepting.store(true, release)
       ↳ callers can create new guards again
```

`clearAll()` is self-contained: no external lock is required. `Profiler::start()`
calls it without `lockAll()`.

---

## rotate() Protocol

`rotate()` is called inside `rotateDictsAndRun()` under a `SignalBlocker` but
**before** `lockAll()`. It is safe without an external lock.

```
rotate()  [SignalBlocker active, no external mutex]

Phase 1:
  old_active = _rot.active()
  _rot.clearTarget()->copyFrom(*old_active)
       ↳ pre-populate the future active buffer with all current entries
  _rot.rotate()
       ↳ old_active becomes the dump buffer; clearTarget becomes new active

Drain:
  RefCountGuard::waitForRefCountToClear(old_active)
       ↳ wait for any JNI thread still holding a guard on old_active
         (signal handlers on THIS thread cannot fire: SignalBlocker)

Phase 2:
  _rot.active()->copyFrom(*old_active)
       ↳ copy any entries inserted into old_active between Phase 1 and the drain
         (late inserts from other threads are captured here)
```

`SignalBlocker` is needed to bound the Phase 1→Phase 2 window: without it, a
profiling signal on the dump thread could keep inserting into `old_active` and
defer `waitForRefCountToClear` indefinitely. It does not provide protection for
JNI threads — those are handled by the RefCountGuard drain.

---

## rotateDictsAndRun() Decomposition

```
rotateDictsAndRun(jfr_op):

  SignalBlocker blocker          ← blocks SIGPROF/SIGVTALRM on THIS thread

  _class_map.rotate()            ┐
  _string_label_map.rotate()     ├ self-contained; no lockAll() needed
  _context_value_map.rotate()    ┘

  lockAll()                      ← gates CallTraceStorage writers
  jfr_op()                       ← writeCpool() reads dump buffers;
                                    lookupDuringDump() may insert
  unlockAll()

  _class_map.clearStandby()      ┐
  _string_label_map.clearStandby()├ clears scratch; resets per-dump counters
  _context_value_map.clearStandby()┘
```

`rotate()` and `lockAll()` are deliberately separated:

- `rotate()` needs `SignalBlocker` (to bound the drain window on this thread) but
  not `lockAll()`.
- `jfr_op()` needs `lockAll()` (to exclude concurrent `CallTraceStorage` writes)
  but rotation is already complete before it runs.

---

## Invariants Summary

| Invariant | Enforced by |
|-----------|-------------|
| No UAF during `clearAll()` reset | Arena keeps key memory valid; drain ensures no reader is mid-table when memset runs |
| No entry lost during `rotate()` | Two-phase copy + `waitForRefCountToClear(old_active)` drains late JNI insertors |
| No profiling signal inserts into `old_active` between Phase 1 and 2 (dump thread) | `SignalBlocker` in `rotateDictsAndRun()` |
| `writeCpool()` sees a stable dump snapshot | `rotate()` completes (including drain) before `jfr_op()` starts |
| `CallTraceStorage` writers excluded during dump | `lockAll()` around `jfr_op()` |
| Dictionary writers NOT excluded during dump | By design: `rotate()`'s two-phase copy absorbs concurrent inserts |
