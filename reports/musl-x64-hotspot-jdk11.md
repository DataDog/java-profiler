---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 10:04:41 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 913 |
| Sample Rate | 15.22/sec |
| Health Score | 951% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (5 unique values: 81-96 cores)</summary>

```
1777557381 96
1777557386 96
1777557391 92
1777557396 92
1777557401 92
1777557406 92
1777557411 92
1777557416 92
1777557421 92
1777557426 92
1777557431 89
1777557436 89
1777557441 89
1777557446 89
1777557451 89
1777557456 89
1777557461 89
1777557466 85
1777557471 85
1777557476 81
```
</details>

---

