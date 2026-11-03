---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 10:59:16 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 411 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1793721274 59
1793721279 59
1793721284 59
1793721289 62
1793721294 62
1793721299 62
1793721304 62
1793721309 62
1793721314 62
1793721319 62
1793721324 62
1793721329 62
1793721334 62
1793721339 62
1793721344 62
1793721349 62
1793721354 62
1793721359 62
1793721364 62
1793721369 64
```
</details>

---

