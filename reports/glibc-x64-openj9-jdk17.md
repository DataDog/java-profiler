---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 08:37:36 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 66-75 cores)</summary>

```
1795440776 73
1795440781 73
1795440786 73
1795440791 73
1795440796 73
1795440801 73
1795440806 73
1795440811 68
1795440816 68
1795440821 68
1795440826 68
1795440831 68
1795440836 68
1795440841 68
1795440846 68
1795440851 66
1795440856 66
1795440861 66
1795440866 66
1795440871 66
```
</details>

---

