---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 19:34:25 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 12 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1770251316 92
1770251321 92
1770251326 92
1770251331 92
1770251336 92
1770251341 92
1770251346 96
1770251351 96
1770251356 96
1770251361 96
1770251366 96
1770251371 96
1770251376 96
1770251381 96
1770251386 96
1770251391 96
1770251396 96
1770251401 96
1770251406 96
1770251411 96
```
</details>

---

