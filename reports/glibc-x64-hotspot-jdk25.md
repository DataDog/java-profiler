---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 14:55:32 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 60-71 cores)</summary>

```
1794945030 60
1794945035 60
1794945040 62
1794945045 62
1794945050 62
1794945055 62
1794945060 62
1794945065 62
1794945070 62
1794945075 62
1794945080 62
1794945085 71
1794945090 71
1794945095 71
1794945100 71
1794945105 71
1794945110 71
1794945115 71
1794945120 71
1794945125 71
```
</details>

---

