---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 13:03:13 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 82-89 cores)</summary>

```
1794851906 84
1794851911 84
1794851916 84
1794851921 84
1794851926 84
1794851932 82
1794851937 82
1794851942 82
1794851947 82
1794851952 82
1794851957 82
1794851962 82
1794851967 84
1794851972 84
1794851977 86
1794851982 86
1794851987 86
1794851992 86
1794851997 86
1794852002 86
```
</details>

---

