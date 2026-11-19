---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:29:51 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 9 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 68-71 cores)</summary>

```
1795098321 69
1795098326 69
1795098331 69
1795098336 69
1795098341 69
1795098346 69
1795098351 69
1795098356 69
1795098361 69
1795098366 69
1795098371 69
1795098376 69
1795098382 69
1795098387 69
1795098392 69
1795098397 71
1795098402 71
1795098407 71
1795098412 71
1795098417 68
```
</details>

---

