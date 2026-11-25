---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 16:19:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 55-57 cores)</summary>

```
1795641293 57
1795641298 57
1795641303 57
1795641308 57
1795641313 57
1795641318 57
1795641323 57
1795641328 57
1795641333 57
1795641338 57
1795641343 57
1795641348 55
1795641353 55
1795641358 55
1795641363 55
1795641368 55
1795641373 55
1795641378 55
1795641383 55
1795641388 55
```
</details>

---

