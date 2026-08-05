---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-05 10:18:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 13 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1785939298 48
1785939303 48
1785939308 48
1785939313 48
1785939318 53
1785939323 53
1785939328 53
1785939333 53
1785939338 53
1785939343 53
1785939348 53
1785939353 53
1785939358 53
1785939363 53
1785939368 53
1785939373 53
1785939379 53
1785939384 53
1785939389 53
1785939394 53
```
</details>

---

