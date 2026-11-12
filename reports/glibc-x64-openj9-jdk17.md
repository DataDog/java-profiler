---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:09:37 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 86-94 cores)</summary>

```
1794495912 86
1794495917 86
1794495922 86
1794495927 86
1794495932 94
1794495937 94
1794495942 94
1794495947 94
1794495952 94
1794495957 94
1794495962 94
1794495967 94
1794495972 94
1794495977 94
1794495982 94
1794495987 94
1794495992 94
1794495998 94
1794496003 94
1794496008 94
```
</details>

---

