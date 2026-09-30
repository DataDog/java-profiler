---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 12:30:28 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 854 |
| Sample Rate | 14.23/sec |
| Health Score | 889% |
| Threads | 10 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (5 unique values: 21-61 cores)</summary>

```
1790785492 29
1790785497 29
1790785503 29
1790785508 29
1790785513 29
1790785518 29
1790785523 32
1790785528 32
1790785533 29
1790785538 29
1790785543 29
1790785548 29
1790785553 21
1790785558 21
1790785563 21
1790785568 21
1790785573 21
1790785578 21
1790785583 21
1790785588 23
```
</details>

---

