---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-14 10:47:49 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1791988920 36
1791988925 36
1791988930 36
1791988935 36
1791988940 36
1791988945 36
1791988950 36
1791988955 36
1791988960 36
1791988965 36
1791988970 36
1791988975 36
1791988980 36
1791988985 36
1791988990 36
1791988995 36
1791989000 36
1791989005 36
1791989010 36
1791989015 48
```
</details>

---

