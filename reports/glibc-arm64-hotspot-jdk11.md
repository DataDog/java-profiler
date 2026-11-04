---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 03:32:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
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
1793781004 48
1793781009 48
1793781014 48
1793781019 48
```
</details>

---

