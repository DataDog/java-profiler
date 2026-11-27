---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-27 10:39:50 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 81-87 cores)</summary>

```
1795793774 81
1795793779 81
1795793784 81
1795793789 81
1795793794 81
1795793799 81
1795793804 81
1795793809 83
1795793814 83
1795793819 83
1795793824 83
1795793829 83
1795793834 83
1795793839 83
1795793844 83
1795793849 83
1795793854 83
1795793859 83
1795793864 83
1795793869 83
```
</details>

---

