---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-20 21:19:10 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 7 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 14 |
| Allocations | 98 |

<details>
<summary>CPU Timeline (4 unique values: 17-52 cores)</summary>

```
1789953260 22
1789953265 22
1789953270 22
1789953275 22
1789953280 22
1789953285 22
1789953290 22
1789953295 22
1789953300 22
1789953305 22
1789953310 22
1789953315 22
1789953320 17
1789953325 17
1789953330 47
1789953335 47
1789953340 47
1789953345 47
1789953350 47
1789953355 47
```
</details>

---

