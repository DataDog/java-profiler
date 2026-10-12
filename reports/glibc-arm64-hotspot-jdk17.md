---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-12 04:42:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1791794350 54
1791794355 54
1791794360 54
1791794365 54
1791794370 54
1791794375 54
1791794380 54
1791794385 54
1791794390 54
1791794395 54
1791794400 54
1791794405 54
1791794410 54
1791794415 54
1791794420 54
1791794425 54
1791794430 49
1791794435 49
1791794440 59
1791794445 59
```
</details>

---

