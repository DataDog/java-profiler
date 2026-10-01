---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-01 06:31:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 173 |
| Sample Rate | 2.88/sec |
| Health Score | 180% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1790850341 32
1790850346 32
1790850351 32
1790850356 32
1790850361 32
1790850366 32
1790850371 32
1790850376 32
1790850381 32
1790850386 32
1790850391 29
1790850396 29
1790850401 29
1790850406 29
1790850411 29
1790850416 29
1790850421 29
1790850426 29
1790850431 29
1790850436 29
```
</details>

---

