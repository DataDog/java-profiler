---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 16:23:58 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 77 |
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
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 69-77 cores)</summary>

```
1794604773 69
1794604778 77
1794604783 77
1794604788 77
1794604793 77
1794604798 77
1794604803 73
1794604808 73
1794604813 73
1794604818 73
1794604823 73
1794604828 73
1794604833 73
1794604838 75
1794604843 75
1794604848 77
1794604853 77
1794604858 77
1794604863 77
1794604868 77
```
</details>

---

