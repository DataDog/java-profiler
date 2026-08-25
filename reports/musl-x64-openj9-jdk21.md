---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-25 10:32:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 12 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 32-61 cores)</summary>

```
1787667825 32
1787667830 40
1787667835 40
1787667840 40
1787667845 40
1787667850 48
1787667855 48
1787667860 48
1787667865 48
1787667870 48
1787667875 48
1787667880 48
1787667885 48
1787667890 56
1787667895 56
1787667900 56
1787667905 56
1787667910 56
1787667915 56
1787667920 56
```
</details>

---

