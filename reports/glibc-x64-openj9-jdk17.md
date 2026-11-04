---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 03:32:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 8 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 42-66 cores)</summary>

```
1793780914 66
1793780919 66
1793780924 66
1793780929 66
1793780934 66
1793780939 42
1793780944 42
1793780949 42
1793780954 42
1793780959 42
1793780964 42
1793780969 42
1793780974 42
1793780979 42
1793780984 42
1793780989 42
1793780994 42
1793780999 42
1793781004 42
1793781009 42
```
</details>

---

