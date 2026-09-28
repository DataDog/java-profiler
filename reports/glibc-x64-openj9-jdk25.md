---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 09:04:51 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (4 unique values: 46-59 cores)</summary>

```
1790600410 46
1790600415 46
1790600420 46
1790600425 46
1790600430 46
1790600435 46
1790600440 57
1790600445 57
1790600450 57
1790600455 57
1790600460 57
1790600465 57
1790600470 57
1790600475 57
1790600480 57
1790600485 57
1790600490 57
1790600495 57
1790600500 57
1790600505 59
```
</details>

---

