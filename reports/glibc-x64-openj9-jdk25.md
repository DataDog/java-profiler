---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:00:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793721254 94
1793721259 94
1793721264 94
1793721269 94
1793721274 94
1793721279 94
1793721284 96
1793721289 96
1793721294 96
1793721299 96
1793721304 96
1793721309 96
1793721314 96
1793721319 96
1793721324 96
1793721329 96
1793721334 96
1793721339 96
1793721344 96
1793721349 96
```
</details>

---

