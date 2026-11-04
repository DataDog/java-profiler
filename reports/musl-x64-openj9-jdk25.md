---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 03:32:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 48-57 cores)</summary>

```
1793780909 48
1793780914 48
1793780919 48
1793780924 48
1793780929 48
1793780934 48
1793780939 48
1793780944 48
1793780949 48
1793780954 48
1793780959 48
1793780964 48
1793780969 48
1793780974 48
1793780979 48
1793780984 48
1793780989 48
1793780994 48
1793780999 48
1793781004 57
```
</details>

---

