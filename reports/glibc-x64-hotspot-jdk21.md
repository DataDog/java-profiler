---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-29 05:44:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (5 unique values: 35-41 cores)</summary>

```
1777455257 38
1777455262 38
1777455267 39
1777455272 39
1777455277 39
1777455282 39
1777455287 39
1777455292 41
1777455297 41
1777455303 41
1777455308 41
1777455313 39
1777455318 39
1777455323 39
1777455328 39
1777455333 41
1777455338 41
1777455343 41
1777455348 36
1777455353 36
```
</details>

---

