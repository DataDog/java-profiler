---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 10:54:18 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 979 |
| Sample Rate | 16.32/sec |
| Health Score | 1020% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (6 unique values: 75-85 cores)</summary>

```
1778165318 85
1778165323 83
1778165328 83
1778165333 83
1778165338 83
1778165343 85
1778165348 85
1778165353 85
1778165358 85
1778165363 85
1778165368 80
1778165373 80
1778165378 80
1778165383 80
1778165388 80
1778165393 80
1778165398 81
1778165403 81
1778165408 81
1778165413 79
```
</details>

---

