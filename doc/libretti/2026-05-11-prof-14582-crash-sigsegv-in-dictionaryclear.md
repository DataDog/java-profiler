---
spec_id: REQ-PROF-14582
source: jira
source_ref: PROF-14582
jira_comment_id: "3244603"
title: "[Crash] SIGSEGV in Dictionary::clear"
status: implemented
clarity_score: null
created: 2026-05-11
implementing_session: impl-20260511-152444
implemented_pr: https://github.com/DataDog/java-profiler/pull/522
---

# [Crash] SIGSEGV in Dictionary::clear

## Crash signature

* Stack-similarity hash: `53fbf099969b056b` (label `dd-crashsig-53fbf099969b056b`)
* Datadog fingerprints observed: `v10.9BAF07DBF7DA7F0D31E7C17BDAF9753B` _(note: this fingerprint is shared with the_ `Profiler::onThreadEnd` cluster — Datadog's fingerprint is coarser than the top library frame in this case; rely on the stack-similarity hash for dedup)

## Summary

5 crash events observed in the last 2 days (2026-05-06 → 2026-05-08) where the topmost library frame is `Dictionary::clear()` inside the dd-trace-java profiler. Distinct from the broader `[Crash] SIGSEGV in Profiler::dump` umbrella (PROF-14550) by the specific top frame. Tracer: `dd-trace-java` `1.62.0_16c6a5fd1f`. Signal: SIGSEGV.

## Top stack frames

```
#0 Dictionary::clear()
... (deeper frames not captured in this triage; relates to the Profiler::dump → JFR write path)
```

## Representative event

* Datadog logs explorer: https://app.datadoghq.com/logs?query=service%3Ainstrumentation-telemetry-data%20%40lib_language%3Ajvm%20%40tags.crash_datadog%3Atrue%20%40tracer_version%3A1.62.0\*%20%40error.is_crash%3Atrue%20%40error.stack.frames.function%3A%22Dictionary\*%22
* Sample organization: org_id 1000043007 (`robaws`), service `robaws`, env `prod`, language `21.0.10`, OS Linux x86_64
* Sample fingerprint id: `fa6915ac-08a6-48d4-8cfd-1d52a7532634`

## Distribution (5 events)

* Top frames split: `Dictionary::clear()` x3, `Dictionary::clear(DictTable*, int)` x2 (variant signatures of the same call site)
* Most events come from EU prod orgs

## Datadog fingerprints in this cluster

* `v10.9BAF07DBF7DA7F0D31E7C17BDAF9753B`

---

_Auto-filed by the_ `crash-to-jira` triage command. Relates to PROF-14550 (Profiler::dump umbrella).

## Audit Trail

- `2026-05-11` — status: `draft` → `implementing` (session `impl-20260511-152444`)
- `2026-05-11` — status: `implementing` → `implemented` (PR https://github.com/DataDog/java-profiler/pull/522)
