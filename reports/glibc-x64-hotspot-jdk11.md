---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-04 09:03:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 26-29 cores)</summary>

```
1770213478 28
1770213483 28
1770213488 28
1770213493 28
1770213498 29
1770213503 29
1770213508 26
1770213513 26
1770213518 27
1770213523 27
1770213528 27
1770213533 27
1770213538 27
1770213543 27
1770213548 29
1770213553 29
1770213558 29
1770213563 29
1770213568 29
1770213573 29
```
</details>

---

