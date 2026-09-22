---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 17:00:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 37-72 cores)</summary>

```
1790110529 72
1790110534 72
1790110539 45
1790110544 45
1790110549 45
1790110554 45
1790110559 45
1790110564 45
1790110569 45
1790110574 45
1790110579 45
1790110584 45
1790110589 37
1790110594 37
1790110599 37
1790110604 37
1790110609 37
1790110614 37
1790110619 37
1790110624 37
```
</details>

---

