---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:07:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 572 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793800919 32
1793800924 32
1793800929 32
1793800934 32
1793800939 32
1793800944 32
1793800949 32
1793800954 32
1793800959 32
1793800964 32
1793800969 32
1793800974 32
1793800979 32
1793800984 32
1793800989 32
1793800994 32
1793800999 32
1793801004 32
1793801009 32
1793801014 32
```
</details>

---

