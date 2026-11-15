---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-15 18:02:45 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1794783534 53
1794783539 53
1794783544 53
1794783549 53
1794783554 53
1794783559 53
1794783564 53
1794783569 53
1794783574 53
1794783579 53
1794783584 53
1794783589 55
1794783594 55
1794783599 55
1794783604 55
1794783609 55
1794783614 55
1794783619 55
1794783624 55
1794783629 55
```
</details>

---

