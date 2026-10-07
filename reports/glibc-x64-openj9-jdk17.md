---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-07 07:29:47 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1791372306 32
1791372311 32
1791372316 32
1791372321 32
1791372326 32
1791372331 30
1791372336 30
1791372341 30
1791372346 30
1791372351 30
1791372356 30
1791372361 30
1791372366 30
1791372371 30
1791372376 30
1791372381 30
1791372386 30
1791372391 30
1791372396 30
1791372401 30
```
</details>

---

