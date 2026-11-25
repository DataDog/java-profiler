---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:21:57 EST

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
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 17-18 cores)</summary>

```
1795641262 18
1795641267 18
1795641272 18
1795641277 18
1795641282 18
1795641287 18
1795641293 18
1795641298 18
1795641303 18
1795641308 17
1795641313 17
1795641318 17
1795641323 17
1795641328 17
1795641333 17
1795641338 17
1795641343 17
1795641348 17
1795641353 17
1795641358 18
```
</details>

---

