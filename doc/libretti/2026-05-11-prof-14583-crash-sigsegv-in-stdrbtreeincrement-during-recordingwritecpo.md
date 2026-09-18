---
spec_id: REQ-PROF-14583
source: jira
source_ref: PROF-14583
jira_key: PROF-14583
jira_comment_id: "3244785"
title: "[Crash] SIGSEGV in std::_Rb_tree_increment during Recording::writeCpool"
status: implemented
clarity_score: null
created: 2026-05-11
implementing_session: impl-20260511-155555
implemented_pr: https://github.com/DataDog/java-profiler/pull/523
---

# [Crash] SIGSEGV in std::_Rb_tree_increment during Recording::writeCpool

## Crash signature

* Stack-similarity hash: `4edf2d97decd942f` (label `dd-crashsig-4edf2d97decd942f`)
* Datadog fingerprints observed: `v10.DAECC680F0728EAB44F26DB0B91B703F` _(distinct from the_ `Profiler::onThreadEnd` and `Profiler::processCallTraces` clusters)

## Summary

3 crash events observed in the last 2 days (2026-05-06 → 2026-05-08) where the topmost frame is `std::_Rb_tree_increment` reached from `Recording::writeCpool` during JFR chunk finalization. Distinct from the `Profiler::processCallTraces` cluster (PROF-14547) — the SEGV happens in the rbtree iterator within `writeCpool` rather than inside the call-trace processing pass. Sibling of the broader `Profiler::dump` umbrella (PROF-14550).

Tracer: `dd-trace-java` `1.62.0_16c6a5fd1f`. Signal: SIGSEGV.

## Top stack frames

```
#0 std::_Rb_tree_increment(std::_Rb_tree_node_base*)
#1 Recording::writeCpool(Buffer*)
#2 Recording::finishChunk(bool)
#3 Recording::switchChunk(int)
#4 FlightRecorder::dump(char const*, int)
#5 Profiler::dump(char const*, int)
#6 Java_com_datadoghq_profiler_JavaProfiler_dump0
```

## Representative event

* Datadog logs explorer: https://app.datadoghq.com/logs?query=service%3Ainstrumentation-telemetry-data%20%40lib_language%3Ajvm%20%40tags.crash_datadog%3Atrue%20%40tracer_version%3A1.62.0\*%20%40error.is_crash%3Atrue
* Sample timestamp: 2026-05-07T21:15:35Z
* Sample organization: org_id 1000000744 (`betclic` / mangas gambling), service `casino.game-launcher.worker`, env `prod`, language `21.0.8`, OS Linux x86_64 (Amazon Corretto 21)
* Sample fingerprint id: `9dca29ee-08a2-451c-b48a-c2278d72ee87`
* TRAPNO 0xd, RAX/R8 = `0xa5f355500467267c` (looks like a poisoned/uninit pointer fed into rbtree increment)

## Datadog fingerprints in this cluster

* `v10.DAECC680F0728EAB44F26DB0B91B703F`

---

_Auto-filed by the_ `crash-to-jira` triage command. Relates to PROF-14550 (Profiler::dump umbrella) and PROF-14547 (writeCpool / writeStackTraces family).
