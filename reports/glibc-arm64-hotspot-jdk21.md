---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-06 08:29:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 9 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 33-53 cores)</summary>

```
1791289518 41
1791289523 41
1791289528 41
1791289533 41
1791289538 41
1791289543 41
1791289548 41
1791289553 53
1791289558 53
1791289563 53
1791289568 53
1791289573 53
1791289578 53
1791289583 53
1791289588 53
1791289593 53
1791289598 53
1791289603 53
1791289608 53
1791289613 53
```
</details>

---

