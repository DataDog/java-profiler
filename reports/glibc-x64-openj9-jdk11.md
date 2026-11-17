---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 07:23:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1794917977 29
1794917982 29
1794917988 29
1794917993 29
1794917998 29
1794918003 29
1794918008 29
1794918013 29
1794918018 29
1794918023 29
1794918028 29
1794918033 29
1794918038 29
1794918043 29
1794918048 29
1794918053 29
1794918058 29
1794918063 29
1794918068 29
1794918073 27
```
</details>

---

