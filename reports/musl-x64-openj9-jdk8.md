---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-15 18:02:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 213 |
| Sample Rate | 3.55/sec |
| Health Score | 222% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 64-66 cores)</summary>

```
1794783534 64
1794783539 66
1794783544 66
1794783549 66
1794783554 66
1794783559 66
1794783564 66
1794783569 66
1794783575 66
1794783580 66
1794783585 66
1794783590 66
1794783595 64
1794783600 64
1794783605 64
1794783610 64
1794783615 64
1794783620 64
1794783625 64
1794783630 64
```
</details>

---

