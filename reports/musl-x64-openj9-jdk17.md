---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 13:18:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 74-79 cores)</summary>

```
1794420784 76
1794420789 76
1794420794 76
1794420799 76
1794420804 74
1794420809 74
1794420814 77
1794420819 77
1794420824 77
1794420829 77
1794420834 77
1794420839 77
1794420844 77
1794420849 77
1794420854 77
1794420859 79
1794420864 79
1794420869 77
1794420874 77
1794420879 77
```
</details>

---

