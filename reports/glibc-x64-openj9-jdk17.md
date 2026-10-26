---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-26 12:41:44 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 87-92 cores)</summary>

```
1793032607 87
1793032612 87
1793032617 87
1793032622 87
1793032627 87
1793032632 87
1793032637 87
1793032642 87
1793032647 87
1793032652 87
1793032657 92
1793032662 92
1793032667 92
1793032672 88
1793032677 88
1793032682 88
1793032687 88
1793032692 90
1793032697 90
1793032702 90
```
</details>

---

