---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 11:08:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 13 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794931387 46
1794931392 46
1794931397 46
1794931402 46
1794931407 46
1794931412 51
1794931417 51
1794931422 51
1794931427 51
1794931432 51
1794931437 51
1794931442 51
1794931447 51
1794931452 51
1794931457 51
1794931462 51
1794931467 51
1794931472 51
1794931477 51
1794931482 51
```
</details>

---

