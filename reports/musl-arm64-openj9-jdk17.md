---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-20 05:46:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (4 unique values: 11-18 cores)</summary>

```
1789897319 13
1789897324 13
1789897329 13
1789897334 13
1789897339 13
1789897344 13
1789897349 11
1789897354 11
1789897359 11
1789897364 11
1789897369 16
1789897374 16
1789897379 16
1789897384 16
1789897389 16
1789897394 18
1789897399 18
1789897404 18
1789897409 18
1789897414 18
```
</details>

---

