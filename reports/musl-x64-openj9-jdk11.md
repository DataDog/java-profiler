---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-14 05:55:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 8 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 947 |
| Sample Rate | 15.78/sec |
| Health Score | 986% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 61-81 cores)</summary>

```
1794653427 81
1794653432 81
1794653437 81
1794653442 81
1794653447 81
1794653452 81
1794653457 81
1794653462 81
1794653467 81
1794653472 81
1794653477 81
1794653482 81
1794653487 81
1794653492 81
1794653497 81
1794653502 61
1794653508 61
1794653513 61
1794653518 61
1794653523 61
```
</details>

---

