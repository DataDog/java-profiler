---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-10 01:02:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 8 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1791608304 12
1791608309 12
1791608314 12
1791608319 12
1791608324 12
1791608329 12
1791608334 12
1791608339 12
1791608344 12
1791608349 12
1791608354 12
1791608359 12
1791608364 12
1791608369 12
1791608374 12
1791608379 12
1791608384 12
1791608389 12
1791608394 12
1791608399 12
```
</details>

---

