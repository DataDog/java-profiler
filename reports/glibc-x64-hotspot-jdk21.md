---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 10:09:36 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1794495920 55
1794495925 55
1794495930 55
1794495935 55
1794495940 55
1794495945 55
1794495950 53
1794495955 53
1794495960 53
1794495965 53
1794495970 55
1794495975 55
1794495980 55
1794495985 55
1794495990 55
1794495995 55
1794496000 55
1794496005 55
1794496010 55
1794496015 55
```
</details>

---

