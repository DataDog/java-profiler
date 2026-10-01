---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 06:31:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 50-88 cores)</summary>

```
1790850341 50
1790850346 50
1790850351 50
1790850356 71
1790850361 71
1790850366 71
1790850371 71
1790850376 88
1790850381 88
1790850386 88
1790850391 88
1790850396 88
1790850401 88
1790850406 88
1790850411 88
1790850416 88
1790850421 88
1790850426 88
1790850431 88
1790850436 88
```
</details>

---

