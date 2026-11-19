---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:58:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (5 unique values: 30-46 cores)</summary>

```
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
1795085665 43
1795085670 43
1795085675 43
1795085680 43
1795085685 45
1795085690 45
1795085695 45
1795085700 45
1795085705 45
```
</details>

---

