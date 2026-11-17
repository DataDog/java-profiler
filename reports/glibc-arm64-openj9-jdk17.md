---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 05:51:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 142 |
| Sample Rate | 2.37/sec |
| Health Score | 148% |
| Threads | 10 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794912473 46
1794912478 46
1794912483 46
1794912488 46
1794912493 46
1794912498 46
1794912503 51
1794912508 51
1794912513 51
1794912518 51
1794912523 51
1794912528 51
1794912533 51
1794912538 51
1794912543 51
1794912548 51
1794912553 51
1794912558 51
1794912563 51
1794912568 51
```
</details>

---

