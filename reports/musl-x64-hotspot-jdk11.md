---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-26 01:03:12 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1790398376 64
1790398381 62
1790398386 62
1790398391 62
1790398396 62
1790398401 62
1790398406 62
1790398411 62
1790398416 62
1790398421 64
1790398426 64
1790398431 66
1790398436 66
1790398441 66
1790398446 66
1790398451 66
1790398456 66
1790398461 66
1790398466 66
1790398471 66
```
</details>

---

