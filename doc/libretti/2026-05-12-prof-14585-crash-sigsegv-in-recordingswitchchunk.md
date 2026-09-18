---
spec_id: REQ-PROF-14585
source: jira
source_ref: PROF-14585
title: "[Crash] SIGSEGV in Recording::switchChunk"
status: draft
clarity_score: null
created: 2026-05-12
implementing_session: null
implemented_pr: null
---

# [Crash] SIGSEGV in Recording::switchChunk

## Crash signature

* Full-stack hash: `07b2657be5f9313a` (label `dd-crashsig-07b2657be5f9313a`)
* Top-frame hash: `e09d60cedafef867` (label `dd-crashsig-top-e09d60cedafef867`) — fallback for partial-stack matches
* Datadog fingerprints observed: `v10.B1A8D6128A089A3347E6EADF45BE9B1A` _(hint only — fingerprint is not 1:1 with this stack; e.g. it may overlap unrelated crashes)_

## Summary

`1` crash event from `1` org / `1` service in the last `1` day, all matching this stack pattern. Tracer: `DataDog/dd-trace-java` `@tracer_version:1.62.0*`. Signal: `SIGSEGV`.

## Top stack frames (normalized)

```
#0 Recording::switchChunk
#1 FlightRecorder::dump
#2 Profiler::dump
#3 Java_com_datadoghq_profiler_JavaProfiler_dump0
```

## Representative event

* [Datadog logs](https://app.datadoghq.com/logs?from_ts=1778149950956&live=false&query=service%3Ainstrumentation-telemetry-data+%40lib_language%3Ajvm+%40tracer_version%3A1.62.0%2A+%40error.is_crash%3Atrue&stream_sort=desc&to_ts=1778236350956) for one example
* Service: `land-guidanceplan`
* Env: `cert`
* OS / arch: `Linux` / `amd64`
* Lang version: `25.0.3`
* Tracer build id: `1.62.0~16c6a5fd1f`
* JVM args: `-javaagent:dd-java-agent.jar -XX:MaxRAMPercentage=75 -XX:+UseZGC -XX:+UseCompactObjectHeaders`

## Distribution

* Envs: `cert:1`
* OS: `Linux:1`
* Arch: `amd64:1`
* Language versions: `{25.0.3}`

## Datadog fingerprints in this cluster

`v10.B1A8D6128A089A3347E6EADF45BE9B1A`

---

_Auto-filed by the_ `crash-to-jira` triage command.
