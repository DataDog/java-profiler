---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-26 09:38:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (5 unique values: 55-61 cores)</summary>

```
1793021600 56
1793021605 56
1793021610 56
1793021615 56
1793021620 56
1793021625 58
1793021630 58
1793021635 58
1793021640 58
1793021645 58
1793021650 58
1793021655 58
1793021660 58
1793021665 58
1793021670 58
1793021675 60
1793021680 60
1793021685 60
1793021690 61
1793021695 61
```
</details>

---

