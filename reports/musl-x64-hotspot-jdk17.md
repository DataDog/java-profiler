---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 03:32:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793780904 30
1793780909 30
1793780914 32
1793780919 32
1793780924 32
1793780929 32
1793780934 32
1793780939 32
1793780944 32
1793780949 32
1793780954 32
1793780959 32
1793780964 32
1793780969 32
1793780974 32
1793780979 32
1793780984 32
1793780989 32
1793780994 32
1793780999 32
```
</details>

---

