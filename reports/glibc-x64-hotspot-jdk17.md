---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-21 07:20:43 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 880 |
| Sample Rate | 14.67/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1787310917 84
1787310922 84
1787310927 86
1787310932 86
1787310937 86
1787310942 86
1787310947 86
1787310952 88
1787310957 88
1787310962 88
1787310967 88
1787310972 88
1787310977 88
1787310982 88
1787310987 88
1787310992 88
1787310997 88
1787311002 88
1787311007 88
1787311012 88
```
</details>

---

