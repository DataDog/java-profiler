---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-21 07:20:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 883 |
| Sample Rate | 14.72/sec |
| Health Score | 920% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1787310896 84
1787310901 84
1787310906 84
1787310911 84
1787310916 84
1787310921 84
1787310926 84
1787310931 86
1787310936 86
1787310942 86
1787310947 86
1787310952 86
1787310957 88
1787310962 88
1787310967 88
1787310972 88
1787310977 88
1787310982 88
1787310987 88
1787310992 88
```
</details>

---

