---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:28:30 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 613 |
| Sample Rate | 10.22/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1789680306 50
1789680311 50
1789680316 50
1789680321 50
1789680326 52
1789680331 52
1789680336 52
1789680341 52
1789680346 52
1789680351 52
1789680356 52
1789680361 52
1789680366 52
1789680371 52
1789680376 52
1789680381 52
1789680386 52
1789680391 52
1789680396 52
1789680401 52
```
</details>

---

