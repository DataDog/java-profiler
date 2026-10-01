---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 08:19:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 29-37 cores)</summary>

```
1790856879 37
1790856884 37
1790856889 37
1790856894 37
1790856899 37
1790856904 37
1790856909 37
1790856914 37
1790856919 37
1790856924 37
1790856929 29
1790856934 29
1790856939 29
1790856944 29
1790856949 29
1790856954 29
1790856959 29
1790856965 29
1790856970 29
1790856975 29
```
</details>

---

