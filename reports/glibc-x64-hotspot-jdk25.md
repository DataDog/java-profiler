---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:30:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 12 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 43-51 cores)</summary>

```
1789737718 43
1789737723 43
1789737728 43
1789737733 51
1789737738 51
1789737743 51
1789737748 51
1789737753 51
1789737758 51
1789737763 51
1789737768 51
1789737773 51
1789737778 51
1789737783 51
1789737788 51
1789737793 51
1789737798 51
1789737803 51
1789737808 51
1789737813 51
```
</details>

---

