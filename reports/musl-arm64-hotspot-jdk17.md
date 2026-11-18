---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:23:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (3 unique values: 49-64 cores)</summary>

```
1795007870 49
1795007875 49
1795007880 49
1795007885 49
1795007890 49
1795007895 49
1795007900 49
1795007905 49
1795007910 51
1795007915 51
1795007920 51
1795007925 51
1795007930 51
1795007935 51
1795007940 64
1795007945 64
1795007950 64
1795007955 64
1795007960 64
1795007965 64
```
</details>

---

