---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:10:50 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 31-48 cores)</summary>

```
1794355410 48
1794355415 48
1794355420 48
1794355425 48
1794355430 48
1794355435 48
1794355440 48
1794355445 48
1794355450 48
1794355455 31
1794355460 31
1794355465 31
1794355470 31
1794355475 31
1794355480 31
1794355485 31
1794355490 31
1794355495 31
1794355500 31
1794355505 31
```
</details>

---

