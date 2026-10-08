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
- **The arena does not make a stale reader safe.** `clear()` keeps only the root table
  and the first arena chunk; overflow nodes and further chunks are freed. A caller whose
  guard `clearAll()`'s drain missed (the TOCTOU gap between the `_accepting` acquire-load
  and `RefCountGuard::count++`) is stopped by the seq_cst `_accepting` recheck after guard
  creation, before it touches buffer data; and if the drain times out, `clearAll()`
  resets nothing (see "The seq_cst recheck after guard creation" and "clearAll() Protocol").
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

                              tryWaitForRefCountsToClear(_a,_b,_c):
                              scan all slots; block until no
                              slot references any of this
                              dictionary's buffers (~500ms cap)

                              → drained: free overflow nodes and
                                extra arena chunks, memset root table
                              → timed out: touch nothing, return false
```

### The seq_cst recheck after guard creation

On weakly-ordered CPUs (ARM64) there is a TOCTOU window between step 1 and step 3:
a caller can load `_accepting == true`, and its guard can become visible only after
`clearAll()`'s drain has scanned its slot.  The caller therefore re-loads `_accepting`
(seq_cst) after creating the guard and returns 0 if it is false, before touching any
buffer data:

```
Thread A (caller)          Thread B (clearAll)
─────────────────          ───────────────────
load _accepting → true
active = _rot.active()
                           _accepting.store(false, seq_cst)
                           drain → sees no guard for A → returns
                           free overflow nodes / extra arena chunks
RefCountGuard guard(...)
load _accepting (seq_cst) → false → return 0   ← never reads the buffer
```

Without the recheck Thread A could read freed overflow nodes or arena chunks: only
the root table and the first arena chunk survive `clear()`.

## clearAll() Protocol

```
clearAll() -> bool
  1. _accepting.store(false, seq_cst)
       ↳ subsequent lookup() / bounded_lookup() callers fail their
         _accepting acquire-load and return 0 immediately
  2. RefCountGuard::tryWaitForRefCountsToClear({&_a, &_b, &_c})
       ↳ drains every caller already past the _accepting load.  Only
         guards on this dictionary's buffers count, so traffic on other
         dictionaries (Profiler::start() resets three back to back) can
         neither delay nor fail it.  A caller whose guard the drain
         missed is caught by the seq_cst recheck (see above).
       ↳ timeout (~500ms): _accepting.store(true), return false.
         Nothing is reset - a guarded caller may still be using the
         storage.  The reset is all-or-nothing: restarting _next_id
         without clearing would reissue ids existing entries use.
  3. _a.clear(); _b.clear(); _c.clear()
       ↳ frees overflow nodes and extra arena chunks, memsets root table
  4. _rot.reset()
  5. _next_id.store(1, relaxed)
  6. reset counters, bump generation()
  7. _accepting.store(true, release)
       ↳ callers can create new guards again
  8. return true
```

`clearAll()` is self-contained: no external lock is required. It only reports the
result; `Profiler::start()` (`resetRecordingState()`) calls it without `lockAll()`,
and for a dictionary that was not reset increments `DICTIONARY_DRAIN_TIMEOUTS` and
logs a warning after `Counters::reset()`, then continues. An unreset dictionary stays
consistent (ids valid, generation unchanged), and the Java `ContextValueCache` is only
invalidated when the context-value dictionary was actually reset.

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
  _string_label_map.clearStandby()├ drains + clears scratch; resets per-dump counters
  _context_value_map.clearStandby()┘
```

`clearStandby()` drains its target buffer before clearing it: a caller whose guard
on the then-active buffer outlived `rotate()`'s drain may still be using it two
rotations later.  If that drain times out the clear is skipped, `clearStandby()`
returns `false` and `rotateDictsAndRun()` reports it (`DICTIONARY_DRAIN_TIMEOUTS`
and a warning).

Reusing such a buffer as-is would not be harmless: the straggler may have inserted
a key after both copies of the earlier `rotate()`, with an id the active buffer has
since assigned differently, and Phase 1's `copyFrom()` keeps an existing entry's id.
So the dictionary remembers the skipped buffer, and the next `rotate()` - which
makes it the active buffer - retries the drain and clear before Phase 1.  Only if
the straggler still holds its guard then (a stall longer than a whole dump cycle)
is the buffer reused uncleared; `rotate()` returns `false` and `rotateDictsAndRun()`
reports it.  The retry is a short series of non-waiting scans, not a full drain,
so a stuck thread does not cost a second ~500 ms timeout per cycle.

If the buffer is reused uncleared, the straggler's stale id wins over the current
one until the next `clearAll()`. Overwriting it with the current id instead would
orphan whatever the straggler recorded under the stale id, so neither choice is
lossless; both require a thread stuck in a guarded insert for a whole dump cycle.

`rotate()` and `lockAll()` are deliberately separated:

- `rotate()` needs `SignalBlocker` (to bound the drain window on this thread) but
  not `lockAll()`.
- `jfr_op()` needs `lockAll()` (to exclude concurrent `CallTraceStorage` writes)
  but rotation is already complete before it runs.

---

## Invariants Summary

| Invariant | Enforced by |
|-----------|-------------|
| No UAF during `clearAll()` reset | Per-dictionary drain + seq_cst `_accepting` recheck; on drain timeout nothing is reset |
| No UAF during `clearStandby()` | Drain of the clear target; on timeout the clear is skipped |
| No entry lost during `rotate()`, unless its drain times out | Two-phase copy + `waitForRefCountToClear(old_active)` drains late JNI insertors; after a release-build timeout an insert by a straggler may miss the dump snapshot (it stays memory-safe: `clearStandby()` drains before clearing) |
| No profiling signal inserts into `old_active` between Phase 1 and 2 (dump thread) | `SignalBlocker` in `rotateDictsAndRun()` |
| `writeCpool()` sees a stable dump snapshot | `rotate()` completes (including drain) before `jfr_op()` starts |
| `CallTraceStorage` writers excluded during dump | `lockAll()` around `jfr_op()` |
| Dictionary writers NOT excluded during dump | By design: `rotate()`'s two-phase copy absorbs concurrent inserts |
