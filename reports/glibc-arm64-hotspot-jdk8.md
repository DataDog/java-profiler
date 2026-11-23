---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-23 05:59:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 28-34 cores)</summary>

```
1795431314 34
1795431319 34
1795431324 34
1795431329 34
1795431334 34
1795431339 34
1795431344 34
1795431349 34
1795431354 34
1795431359 34
1795431364 34
1795431369 34
1795431374 34
1795431379 34
1795431384 34
1795431389 34
1795431394 30
1795431399 30
1795431404 28
1795431409 28
```
</details>

---

