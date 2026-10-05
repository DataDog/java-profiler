---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-05 16:36:23 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 913 |
| Sample Rate | 15.22/sec |
| Health Score | 951% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791232295 46
1791232300 46
1791232305 46
1791232310 46
1791232315 46
1791232320 46
1791232325 51
1791232330 51
1791232335 51
1791232340 51
1791232345 51
1791232350 51
1791232355 51
1791232360 51
1791232365 51
1791232370 51
1791232375 51
1791232380 51
1791232385 51
1791232390 51
```
</details>

---

