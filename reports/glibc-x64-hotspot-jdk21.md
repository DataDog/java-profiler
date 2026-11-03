---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-03 11:22:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1793722632 86
1793722637 86
1793722642 86
1793722647 86
1793722652 86
1793722657 86
1793722662 86
1793722667 84
1793722672 84
1793722677 84
1793722682 84
1793722687 84
1793722692 84
1793722697 84
1793722702 84
1793722707 84
1793722712 82
1793722717 82
1793722722 82
1793722727 82
```
</details>

---

