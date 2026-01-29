---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-29 07:49:58 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 14.33/sec |
| Health Score | 896% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 21.97/sec |
| Health Score | 1373% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 22-48 cores)</summary>

```
1769690632 22
1769690637 22
1769690642 22
1769690647 22
1769690652 22
1769690657 22
1769690662 22
1769690667 22
1769690672 22
1769690677 22
1769690682 22
1769690687 22
1769690692 48
1769690697 48
1769690702 48
1769690707 48
1769690712 48
1769690717 48
1769690722 48
1769690727 48
```
</details>

---

