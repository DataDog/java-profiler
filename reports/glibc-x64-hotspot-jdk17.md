---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 10:54:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 800 |
| Sample Rate | 13.33/sec |
| Health Score | 833% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 51-65 cores)</summary>

```
1778165328 51
1778165333 51
1778165338 51
1778165343 55
1778165348 55
1778165353 55
1778165358 55
1778165363 55
1778165368 55
1778165373 55
1778165378 55
1778165383 55
1778165388 55
1778165393 55
1778165398 55
1778165403 55
1778165408 55
1778165413 65
1778165418 65
1778165423 65
```
</details>

---

