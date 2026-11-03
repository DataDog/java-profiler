---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:00:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 36-41 cores)</summary>

```
1793721189 36
1793721194 36
1793721199 36
1793721204 36
1793721209 36
1793721214 36
1793721219 41
1793721224 41
1793721229 41
1793721234 41
1793721239 41
1793721244 41
1793721249 41
1793721254 41
1793721259 41
1793721264 41
1793721269 41
1793721274 41
1793721279 41
1793721284 41
```
</details>

---

