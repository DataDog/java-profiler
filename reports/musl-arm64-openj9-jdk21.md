---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 09:05:28 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (4 unique values: 9-30 cores)</summary>

```
1786971565 30
1786971570 30
1786971575 30
1786971580 30
1786971585 30
1786971590 30
1786971595 30
1786971600 30
1786971605 30
1786971610 30
1786971615 30
1786971620 30
1786971625 20
1786971630 20
1786971635 9
1786971641 9
1786971646 9
1786971651 9
1786971656 9
1786971661 9
```
</details>

---

