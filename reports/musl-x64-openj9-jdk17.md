---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:22:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 779 |
| Sample Rate | 12.98/sec |
| Health Score | 811% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 15-24 cores)</summary>

```
1795007915 15
1795007920 15
1795007925 15
1795007930 15
1795007935 15
1795007940 15
1795007945 15
1795007950 15
1795007955 24
1795007960 24
1795007965 24
1795007970 24
1795007975 24
1795007980 24
1795007985 24
1795007990 24
1795007995 24
1795008000 22
1795008005 22
1795008010 22
```
</details>

---

