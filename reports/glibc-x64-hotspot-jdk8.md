---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-29 16:31:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 51-62 cores)</summary>

```
1793305597 51
1793305602 51
1793305607 53
1793305612 53
1793305617 53
1793305622 62
1793305627 62
1793305632 62
1793305637 62
1793305642 62
1793305647 62
1793305652 62
1793305657 62
1793305662 62
1793305667 62
1793305672 62
1793305677 62
1793305682 62
1793305687 62
1793305692 62
```
</details>

---

