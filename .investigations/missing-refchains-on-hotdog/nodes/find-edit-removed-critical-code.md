---
id: find-edit-removed-critical-code
type: lesson
status: confirmed
tags: [methodology, edit-safety, regression, lesson, NEW-THIS-SESSION]
created: 20260915
updated: 20260915
---

# Edit accidentally removed a critical algorithm loop

## What happened

While removing a TEMP diagnostic from `admitStaticFieldRoots()` in
`referenceChains.cpp`, the `edit` tool's `oldText` matched the entire
block containing BOTH the diagnostic code AND the original holder-fill
`for` loop:

```cpp
    for (jint i = 0; i < chunk_count; i++) {
      // TEMP DIAGNOSTIC ...
      { ... GetClassSignature ... }
      jni->SetObjectArrayElement(holder, i, classes[chunk_end - 1 - i]);
      if (jniExceptionCheck(jni)) { holder = nullptr; break; }
    }
```

The replacement `newText` was just `}` — the closing brace of the
surrounding `if (holder != nullptr)` block. This silently deleted the
entire holder-fill loop, leaving the holder array empty. The sweep
would have admitted zero static fields — a silent total regression.

The build compiled clean (syntactically valid: an empty `if` block).
The bug was caught only by reviewing the full `git diff` afterward.

## Root cause

The diagnostic was interleaved INSIDE the existing `for` loop body.
Removing the diagnostic by replacing the whole `for` block removed the
original code along with it. The `edit` tool has no concept of
"original code vs. diagnostic code" — it matches text, and the
`oldText` spanned both.

## Prevention rules

1. **Never replace a block that mixes diagnostic code with original
   code.** When removing a diagnostic that was interleaved into existing
   logic, edit to restore the original lines, not to delete the whole
   block. The `oldText` should be the diagnostic lines only; the
   `newText` should be empty or the original lines without the
   diagnostic.

2. **Always review the full `git diff` after edits, before building.**
   A compiling build does NOT prove correctness — a missing loop is
   syntactically valid. The diff is the only safety net.

3. **When a diagnostic is inside a loop, prefer adding a separate
   `TEST_LOG` line BEFORE or AFTER the loop, not interleaved inside it.**
   A diagnostic that sits in its own statement is trivial to remove
   without touching surrounding code.

4. **If the diagnostic MUST inspect per-iteration state, add it as a
   minimal inline check** (e.g., a single `if` + `TEST_LOG`), never a
   multi-line block that visually merges with the loop body. Remove by
   deleting only those lines.

5. **Diff against the version BEFORE the diagnostic was added, not the
   version with the diagnostic.** `git diff <pre-diagnostic-commit> --
   <file>` shows whether the only changes are the diagnostic removal.
