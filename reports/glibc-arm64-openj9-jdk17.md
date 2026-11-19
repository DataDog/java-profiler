---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 05:58:28 EST

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
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 8 |
| Allocations | 313 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (6 unique values: 29-46 cores)</summary>

```
1795085585 29
1795085590 30
1795085595 30
1795085600 30
1795085605 30
1795085610 30
1795085615 30
1795085620 44
1795085625 44
1795085630 46
1795085635 46
1795085640 46
1795085645 43
1795085650 43
1795085655 43
1795085660 43
1795085666 43
1795085671 43
1795085676 43
1795085681 43
```
</details>

---

