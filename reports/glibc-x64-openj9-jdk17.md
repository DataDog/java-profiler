---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:25:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (3 unique values: 68-71 cores)</summary>

```
1795015296 71
1795015301 71
1795015306 71
1795015311 69
1795015316 69
1795015321 69
1795015326 69
1795015331 69
1795015336 69
1795015341 69
1795015346 71
1795015351 71
1795015356 71
1795015361 71
1795015366 68
1795015371 68
1795015376 68
1795015382 68
1795015387 68
1795015392 68
```
</details>

---

