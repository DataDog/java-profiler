---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-16 12:13:02 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 12 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 68-71 cores)</summary>

```
1789574781 71
1789574786 71
1789574791 71
1789574796 71
1789574801 71
1789574806 71
1789574811 71
1789574816 71
1789574821 71
1789574826 71
1789574831 71
1789574836 71
1789574841 68
1789574846 68
1789574851 68
1789574856 68
1789574861 68
1789574866 68
1789574871 68
1789574876 68
```
</details>

---

