---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 05:58:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 9 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (7 unique values: 20-32 cores)</summary>

```
1795085585 26
1795085590 26
1795085595 26
1795085600 26
1795085605 26
1795085610 28
1795085615 28
1795085620 28
1795085625 28
1795085630 28
1795085635 28
1795085640 28
1795085645 28
1795085650 28
1795085655 28
1795085660 27
1795085665 27
1795085670 32
1795085675 32
1795085680 32
```
</details>

---

