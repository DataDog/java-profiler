# Spec: use-of-default-tostring-default-tostring

PR 801 review fixes (run `2026-10-20T17:45:00Z-addr-learn-pr801-retry3`). Five
change requests in the reference-chains test code and the `utils/refchains-*`
tooling. Ground truth for the design: `.sphinx/address/design.md`.

## Problem

1. **4268414107.** The noise-handoff failure message in
   `LeakTagCorrelationScenario.java` concatenates `noiseRepresentative`. Its type
   is `NoisePayload`, which has no `toString()` override, so the message prints
   `ClassName@hash`. Only whether the object is present matters for diagnosis.
2. **4326370498.** `utils/refchains-jfr-metrics.py` runs the bare `jfr` from
   PATH, even when `REFCHAINS_JAVA_HOME` selects the JDK the repro ran on. A
   missing or older `jfr` fails. The sweep then discards stderr and records a
   silent `0 0 -1`.
3. **4326370538.** Each `dump()` switches the chunk, so each snapshot file is
   one chunk whose `jfr summary` Start is the previous dump. Cached chains are
   re-stamped into every dump. The sweep runs the parser once per file and takes
   the min of the per-file "chain − chunk start" values. That converges to about
   one dump interval, not the time since run start. Also, the bash `-ge`/`-lt`
   comparisons on `%.3f` floats never succeed, so `time_to_first_chain_s`
   always stays `-1`.
4. **4326370566.** `utils/compare-refchains-repro.sh` swallows each variant's
   exit status. Missing metrics are then parsed as zeros, and the script emits
   definitive conclusions from a failed experiment.
5. **4326370585.** The new refchains scripts lack the Datadog copyright header
   that AGENTS.md requires.

## Correct behaviour

### A. Test diagnostics
- The message prints `representative=null` or `representative=present`, using
  `(noiseRepresentative == null ? "null" : "present")`. The ternary must be in
  parentheses.
- The throw condition, the following
  `setKlassPopulationRepresentativeForTest0` call, and the nulling of the local
  do not change.
- `NoisePayload` gets no `toString()`.

### B. JFR metrics pipeline
- **I-B1 (origin).** Time-to-first-chain (ttf) is measured from the ORIGINAL
  recording start. The per-file origin is chosen in this order:
  1. `jdk.ActiveRecording.recordingStart`
  2. else that event's `startTime`
  3. else the `jfr summary` Start
- **I-B2 (aggregation).** `refchains-jfr-metrics.py` accepts 1..N snapshot
  paths and prints ONE aggregate:
  - `chain_count` = sum of `datadog.ReferenceChain` events over all read files.
  - `abandoned_count` = sum of `datadog.ReferenceChainAbandoned` events.
  - `ttf = max(0, min(all chain startTimes) − min(all origins))`.
  - The sweep invokes it exactly once per run, with every snapshot file of that
    run.
- **I-B3 (sentinel).** No chain, or no origin, gives ttf printed as `-1.000`.
- **I-B4 (jfr selection).**
  - `REFCHAINS_JAVA_HOME` set and non-empty: use `$REFCHAINS_JAVA_HOME/bin/jfr`
    if it is an executable regular file. Otherwise print to stderr
    `error: <path> not found/executable - check REFCHAINS_JAVA_HOME` and exit 1
    immediately. Never fall back to PATH.
  - Unset or empty: use `jfr` from PATH.
  - Resolution happens once, before any file is read.
- **I-B5 (failure visibility).**
  - If a `jfr` invocation fails (non-zero exit or `OSError`) or its output is not
    valid JSON, that file is skipped with a stderr warning.
  - If no file was read, exit non-zero.
  - The sweep no longer discards the parser's stderr. When the parser fails,
    the sweep prints
    `WARN: refchains-jfr-metrics failed for '<label>'; recording 0 0 -1` to
    stderr, records `0 0 -1` and continues.
- **I-B6 (shell portability).**
  - bash 3.2 with `set -euo pipefail`.
  - Never expand an empty array under `set -u`: the guard is `n_snaps -gt 0`.
  - No `declare -A`.
  - No numeric bash comparisons on floats.
- **I-B7 (output contract).**
  - Python stdout is exactly one line, `<int> <int> <float .3f>`.
  - `parse_run` echoes 13 fields in the same order.
  - The CSV header and column order are unchanged.
  - The float ttf reaches the CSV verbatim.
- Timestamp parsing accepts:
  - epoch-millis numbers;
  - ISO strings with `Z` or a numeric offset;
  - 0–9 fractional digits (normalised to 6).
  A naive datetime is treated as UTC. Unparseable values are ignored, never
  fatal.

### C. Compare-run validity
- **I-C1.** A variant that exits non-zero, or exits 0 without a `^[metrics]`
  line, causes:
  - `FAIL: variant '<label>' …` on stderr;
  - after BOTH variants have run, `report.md` rewritten as an `INVALID` report
    that names the failed variants (`<label>(exit=<rc>)` /
    `<label>(no-metrics)`) and the log dir;
  - `FAIL: comparison aborted …` on stderr;
  - exit 1;
  - no comparison table, no "Answers" section, and no `pct_delta`/parse step
    run.
- **I-C2.** When both variants succeed, the output does not change.
- The abort check is at top level, not inside `parse_variant`, which runs in a
  `$(...)`.

### D. Copyright headers
- **I-D1.** Each listed file keeps line 1 = its original shebang and has
  line 2 = `# Copyright 2026, Datadog, Inc`. No other line changes.
- In the Python files the module docstring stays the module docstring.
- `utils/vendor/chart.umd.min.js` is untouched.

## Constraints
- POSIX bash utilities. The sibling scripts deliberately support macOS
  `/bin/bash` 3.2.
- Python: stdlib only. Must run on Python ≥3.7, so do not rely on 3.11+
  `fromisoformat` leniency.
- No new CLI flags or env vars. `REFCHAINS_JAVA_HOME` is already inherited by
  the sweep's `python3` child.
- Sweep policy stays WARN-and-continue for a single bad point.
- Java test code: follow the existing style. Spotless runs before commit.

## Scope

### Primary fixes
- `ddprof-test/src/test/java/com/datadoghq/profiler/referencechains/LeakTagCorrelationScenario.java:264`
  — implicit `Object.toString()` in a diagnostic — print present/null instead.
- `utils/refchains-jfr-metrics.py:24` — tool resolved from PATH instead of the
  selected JDK — add `resolve_jfr()` / `JFR_BIN`, with a hard failure and no
  fallback.
- `utils/sweep-refchains-all.sh:161` (+ `utils/refchains-jfr-metrics.py` main)
  — wrong time origin and wrong aggregation across chunks — aggregate all
  snapshots in one Python call, measured from `jdk.ActiveRecording`.
- `utils/compare-refchains-repro.sh:56` — swallowed child exit status — record
  failures and abort with an INVALID report and exit 1.
- `utils/run-refchains-repro.sh:1` (+ 6 other new scripts) — missing copyright
  header — insert line 2.

### Auto-expanded sibling fixes
- `utils/sweep-refchains-all.sh:158-162` — integer `[ -ge ]`/`[ -lt ]` on
  `%.3f` floats (bash numeric test on a non-integer).
  - Evidence: `per_ttf` comes from `printf "%.3f"` in the Python script, and
    `[ "12.345" -ge 0 ]` is a bash "integer expression expected" error inside
    `if`, so the branch never runs.
  - FLOW: sweep main loop → `parse_run` → per-snapshot loop → `[ "${per_ttf}" -ge 0 ]`.
  - PRECONDITION: at least one chain event, so Python prints a non-negative
    float.
  - REACHABLE: yes.
  - CONCLUSION: medium. ttf is always -1 in the CSV. It is eliminated by the B2
    rewrite, which removes all bash float math.
- `utils/run-chaos-harness.sh:1` — PR-modified file with no Datadog header.
  - Evidence: AGENTS.md "If modifying a file that does not contain Datadog
    copyright, add one". `git diff --diff-filter=M origin/main...HEAD` shows
    the file modified, and `head` shows no header.
  - FLOW: n/a (repository policy).
  - PRECONDITION: the file is modified in this PR.
  - REACHABLE: yes (policy).
  - CONCLUSION: low. Add the same line-2 header.

Known, deliberately NOT fixed: the `wait … || echo WARN` lines in
`sweep-refchains-all.sh` (~L193) and `sweep-refchains-budgets.sh` (~L159). A
sweep continues past a bad point by design.

## Assumptions
- resolved at >=90%: `jfr print --json` renders `jdk.ActiveRecording.recordingStart`
  as an ISO timestamp, because F_TIME_MILLIS maps to
  `@Timestamp(MILLISECONDS_SINCE_EPOCH)`. `parse_ts` also accepts epoch
  millis, and two fallbacks exist.
- resolved at >=90%: a normal bounded repro run exits 0. The only
  `System.exit` calls are `exit(1)` on argument errors, and
  `run-refchains-repro.sh` `exec`s java.
- resolved at >=90%: for the sweep, the policy for a metrics-extraction failure
  is a visible WARN plus `0 0 -1`, not an abort.
- resolved at >=90%: the copyright year is 2026 (HEAD commit date
  2026-10-20), in the same form as `utils/run-containers-tests.sh:2`.
- `chain_count` summed across snapshots counts re-emissions, not distinct
  chains. This behaviour is unchanged and out of scope.
- ttf resolution is one dump cadence, which is inherent to the data.
