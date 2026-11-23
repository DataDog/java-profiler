---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:59:58 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 61-68 cores)</summary>

```
1795431306 61
1795431311 61
1795431316 61
1795431321 66
1795431326 66
1795431331 66
1795431336 66
1795431341 66
1795431346 66
1795431351 66
1795431356 66
1795431361 66
1795431366 66
1795431371 66
1795431376 66
1795431381 66
1795431386 66
1795431391 66
1795431396 66
1795431401 68
```
</details>

---

