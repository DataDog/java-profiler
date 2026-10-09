---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-09 01:05:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 6 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1791522035 64
1791522040 64
1791522045 64
1791522050 64
1791522055 64
1791522060 64
1791522065 59
1791522070 59
1791522075 59
1791522080 59
1791522085 59
1791522090 59
1791522095 59
1791522100 59
1791522105 59
1791522110 59
1791522115 64
1791522120 64
1791522125 64
1791522130 64
```
</details>

---

