---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 08:48:43 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 933 |
| Sample Rate | 15.55/sec |
| Health Score | 972% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1795095819 58
1795095824 58
1795095829 58
1795095834 58
1795095839 58
1795095844 58
1795095849 58
1795095854 58
1795095859 58
1795095864 58
1795095869 58
1795095874 58
1795095880 58
1795095885 58
1795095890 56
1795095895 56
1795095900 56
1795095905 56
1795095910 56
1795095915 56
```
</details>

---

