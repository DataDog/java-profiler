---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 16:23:58 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 10 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 57-67 cores)</summary>

```
1794604763 65
1794604768 65
1794604773 65
1794604778 67
1794604783 67
1794604788 67
1794604793 67
1794604798 67
1794604803 67
1794604808 67
1794604813 67
1794604818 67
1794604823 67
1794604828 67
1794604833 67
1794604838 67
1794604843 67
1794604848 67
1794604853 67
1794604858 67
```
</details>

---

