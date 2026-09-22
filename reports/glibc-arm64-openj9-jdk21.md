---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 11:34:55 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 200 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (4 unique values: 14-44 cores)</summary>

```
1790090957 19
1790090962 19
1790090967 19
1790090972 19
1790090977 19
1790090982 14
1790090987 14
1790090992 29
1790090997 29
1790091002 29
1790091007 29
1790091012 29
1790091017 29
1790091022 29
1790091027 29
1790091032 29
1790091037 29
1790091042 29
1790091047 29
1790091052 29
```
</details>

---

