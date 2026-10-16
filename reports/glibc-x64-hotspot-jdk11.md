---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-16 06:16:39 EDT

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 892 |
| Sample Rate | 14.87/sec |
| Health Score | 929% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1792145518 62
1792145523 62
1792145528 62
1792145533 62
1792145538 62
1792145543 62
1792145548 62
1792145553 62
1792145558 62
1792145563 62
1792145568 62
1792145573 62
1792145578 62
1792145583 62
1792145588 60
1792145593 60
1792145598 60
1792145603 60
1792145608 60
1792145613 60
```
</details>

---

