---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 18:53:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (5 unique values: 41-59 cores)</summary>

```
1794440885 59
1794440890 59
1794440895 57
1794440900 57
1794440905 57
1794440910 57
1794440915 55
1794440920 55
1794440925 55
1794440930 55
1794440935 55
1794440940 55
1794440945 55
1794440950 55
1794440955 55
1794440960 55
1794440965 55
1794440970 55
1794440975 55
1794440980 43
```
</details>

---

