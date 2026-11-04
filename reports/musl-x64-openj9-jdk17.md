---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 09:07:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 51-67 cores)</summary>

```
1793800914 53
1793800919 53
1793800924 53
1793800929 51
1793800934 51
1793800939 51
1793800944 51
1793800949 51
1793800954 51
1793800959 53
1793800964 53
1793800969 53
1793800974 53
1793800979 53
1793800984 53
1793800989 67
1793800994 67
1793800999 67
1793801004 67
1793801009 67
```
</details>

---

