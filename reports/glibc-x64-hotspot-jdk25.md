---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 18:10:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 51-68 cores)</summary>

```
1795129609 51
1795129614 51
1795129619 51
1795129624 51
1795129629 53
1795129634 53
1795129639 53
1795129644 53
1795129649 53
1795129654 53
1795129659 53
1795129664 63
1795129669 63
1795129674 68
1795129679 68
1795129684 68
1795129689 68
1795129694 68
1795129699 68
1795129704 68
```
</details>

---

