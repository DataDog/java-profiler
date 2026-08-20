---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-19 21:19:12 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 12 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787188523 29
1787188528 29
1787188533 29
1787188538 29
1787188543 29
1787188548 29
1787188553 34
1787188558 34
1787188563 34
1787188568 34
1787188573 34
1787188578 34
1787188583 34
1787188588 34
1787188593 34
1787188598 34
1787188603 34
1787188608 34
1787188613 34
1787188618 34
```
</details>

---

