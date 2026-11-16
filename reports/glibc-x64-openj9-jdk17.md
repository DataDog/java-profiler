---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 11:32:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 10 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 81-93 cores)</summary>

```
1794846438 93
1794846443 93
1794846449 89
1794846454 89
1794846459 89
1794846464 89
1794846469 89
1794846474 89
1794846479 89
1794846484 89
1794846489 89
1794846494 87
1794846499 87
1794846504 87
1794846509 87
1794846514 87
1794846519 87
1794846524 83
1794846529 83
1794846534 83
```
</details>

---

