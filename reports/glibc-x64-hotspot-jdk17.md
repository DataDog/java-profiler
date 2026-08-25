---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-25 15:07:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 40-64 cores)</summary>

```
1787684468 40
1787684473 40
1787684478 40
1787684483 48
1787684488 48
1787684493 48
1787684498 48
1787684503 48
1787684508 48
1787684513 48
1787684518 48
1787684523 48
1787684528 48
1787684533 48
1787684538 48
1787684543 56
1787684548 56
1787684553 56
1787684558 56
1787684563 56
```
</details>

---

