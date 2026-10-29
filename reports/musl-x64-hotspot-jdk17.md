---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-29 11:32:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 11-16 cores)</summary>

```
1793287645 16
1793287650 16
1793287655 16
1793287660 16
1793287665 14
1793287670 14
1793287675 14
1793287680 14
1793287685 14
1793287690 14
1793287695 16
1793287700 16
1793287705 14
1793287710 14
1793287715 14
1793287720 14
1793287725 16
1793287730 16
1793287736 11
1793287741 11
```
</details>

---

