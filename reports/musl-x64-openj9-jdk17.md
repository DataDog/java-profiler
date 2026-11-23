---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 05:28:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 59-67 cores)</summary>

```
1795429459 59
1795429464 59
1795429469 61
1795429474 61
1795429479 59
1795429484 59
1795429489 64
1795429494 64
1795429499 64
1795429504 64
1795429509 64
1795429514 64
1795429519 64
1795429524 64
1795429529 64
1795429534 64
1795429539 64
1795429544 64
1795429549 64
1795429554 67
```
</details>

---

