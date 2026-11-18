---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:22:48 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 10 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 67-96 cores)</summary>

```
1795007895 67
1795007900 67
1795007905 67
1795007910 67
1795007915 67
1795007920 67
1795007925 67
1795007930 67
1795007935 67
1795007940 67
1795007945 67
1795007950 67
1795007955 69
1795007960 69
1795007965 69
1795007970 69
1795007975 71
1795007980 71
1795007985 71
1795007990 71
```
</details>

---

