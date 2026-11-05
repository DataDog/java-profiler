---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 11:16:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 392 |
| Sample Rate | 6.53/sec |
| Health Score | 408% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 20-29 cores)</summary>

```
1793895040 20
1793895045 20
1793895050 20
1793895055 20
1793895060 20
1793895065 20
1793895070 20
1793895075 20
1793895080 20
1793895085 20
1793895090 20
1793895095 20
1793895100 20
1793895105 20
1793895110 20
1793895115 20
1793895120 29
1793895125 29
1793895130 29
1793895135 29
```
</details>

---

