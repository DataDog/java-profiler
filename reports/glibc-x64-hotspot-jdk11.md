---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-09 21:24:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 8 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1786324675 38
1786324680 38
1786324685 38
1786324690 46
1786324695 46
1786324700 48
1786324705 48
1786324710 48
1786324715 48
1786324720 48
1786324725 48
1786324730 48
1786324735 48
1786324740 48
1786324745 48
1786324750 48
1786324755 48
1786324760 48
1786324765 48
1786324770 48
```
</details>

---

