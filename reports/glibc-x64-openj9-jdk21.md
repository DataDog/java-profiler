---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 08:52:14 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1794836859 25
1794836864 25
1794836869 25
1794836874 25
1794836879 27
1794836884 27
1794836889 27
1794836894 27
1794836899 27
1794836904 27
1794836909 27
1794836914 27
1794836919 27
1794836924 27
1794836929 27
1794836934 27
1794836939 25
1794836944 25
1794836949 25
1794836954 25
```
</details>

---

