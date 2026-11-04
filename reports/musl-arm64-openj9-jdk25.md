---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 15:01:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 13 |
| Allocations | 124 |

<details>
<summary>CPU Timeline (2 unique values: 30-51 cores)</summary>

```
1793822230 51
1793822235 51
1793822240 51
1793822245 51
1793822250 51
1793822255 51
1793822260 51
1793822265 51
1793822270 51
1793822275 51
1793822280 51
1793822285 51
1793822290 51
1793822295 51
1793822300 51
1793822305 30
1793822310 30
1793822315 30
1793822320 30
1793822325 30
```
</details>

---

