---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 08:22:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 22-23 cores)</summary>

```
1795007915 23
1795007920 23
1795007925 23
1795007930 23
1795007935 23
1795007940 23
1795007945 23
1795007950 23
1795007955 23
1795007960 23
1795007965 23
1795007970 22
1795007975 22
1795007980 22
1795007985 22
1795007990 22
1795007995 22
1795008000 22
1795008005 22
1795008010 22
```
</details>

---

