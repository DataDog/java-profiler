---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:48:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 7 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791391372 43
1791391377 43
1791391382 43
1791391387 43
1791391392 43
1791391397 48
1791391402 48
1791391407 48
1791391412 43
1791391417 43
1791391422 43
1791391427 43
1791391432 43
1791391437 43
1791391442 43
1791391447 43
1791391452 43
1791391457 43
1791391462 48
1791391467 48
```
</details>

---

