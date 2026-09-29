---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 05:18:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 49-53 cores)</summary>

```
1790673297 53
1790673302 53
1790673307 53
1790673312 53
1790673317 53
1790673322 53
1790673327 53
1790673332 51
1790673337 51
1790673342 49
1790673347 49
1790673352 49
1790673357 49
1790673362 49
1790673367 49
1790673372 49
1790673377 49
1790673382 49
1790673387 49
1790673392 49
```
</details>

---

