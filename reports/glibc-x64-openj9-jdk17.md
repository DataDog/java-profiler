---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 11:22:15 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 24-26 cores)</summary>

```
1793722617 26
1793722622 26
1793722627 26
1793722632 26
1793722637 26
1793722642 26
1793722647 26
1793722652 26
1793722657 26
1793722662 26
1793722667 26
1793722672 24
1793722677 24
1793722682 24
1793722687 24
1793722692 24
1793722697 24
1793722702 24
1793722707 24
1793722712 26
```
</details>

---

