---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 15:01:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 10 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 212 |
| Sample Rate | 3.53/sec |
| Health Score | 221% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 10-44 cores)</summary>

```
1793822275 10
1793822280 10
1793822285 10
1793822290 10
1793822295 10
1793822300 10
1793822305 10
1793822310 44
1793822315 44
1793822320 10
1793822325 10
1793822330 10
1793822335 10
1793822340 10
1793822345 10
1793822350 10
1793822355 10
1793822360 10
1793822365 10
1793822370 10
```
</details>

---

