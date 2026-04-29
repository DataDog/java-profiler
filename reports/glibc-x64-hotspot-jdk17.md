---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-29 05:44:23 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 9 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (4 unique values: 30-36 cores)</summary>

```
1777455287 36
1777455292 36
1777455297 36
1777455302 36
1777455307 34
1777455312 34
1777455317 34
1777455322 34
1777455327 36
1777455332 36
1777455337 32
1777455342 32
1777455347 32
1777455352 32
1777455357 32
1777455362 32
1777455367 32
1777455372 32
1777455377 32
1777455382 32
```
</details>

---

