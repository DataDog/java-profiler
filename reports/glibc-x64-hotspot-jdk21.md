---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-09 21:24:17 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 91 |
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
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 91-94 cores)</summary>

```
1786324665 94
1786324670 94
1786324675 94
1786324680 94
1786324685 94
1786324690 91
1786324695 91
1786324700 91
1786324705 91
1786324710 91
1786324715 91
1786324720 91
1786324725 91
1786324730 91
1786324735 91
1786324740 91
1786324745 91
1786324750 91
1786324755 91
1786324760 91
```
</details>

---

