---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-29 12:43:40 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 18.83/sec |
| Health Score | 1177% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 922 |
| Sample Rate | 30.73/sec |
| Health Score | 1921% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 51-61 cores)</summary>

```
1769708285 51
1769708290 51
1769708295 51
1769708300 51
1769708305 51
1769708310 51
1769708315 51
1769708321 60
1769708326 60
1769708331 60
1769708336 60
1769708341 60
1769708346 60
1769708351 60
1769708356 60
1769708361 60
1769708366 60
1769708371 60
1769708376 60
1769708381 60
```
</details>

---

