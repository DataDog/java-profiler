---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-09 05:04:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 14 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1775724980 43
1775724985 43
1775724990 43
1775724995 43
1775725000 43
1775725005 43
1775725010 43
1775725015 48
1775725020 48
1775725025 48
1775725030 48
1775725035 48
1775725040 48
1775725045 48
1775725050 48
1775725055 48
1775725060 48
1775725065 48
1775725070 48
1775725075 48
```
</details>

---

