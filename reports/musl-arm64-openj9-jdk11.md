---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-20 21:20:07 EDT

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 950 |
| Sample Rate | 15.83/sec |
| Health Score | 989% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1789953269 34
1789953274 34
1789953279 34
1789953284 34
1789953289 34
1789953294 34
1789953299 34
1789953305 34
1789953310 34
1789953315 34
1789953320 34
1789953325 34
1789953330 34
1789953335 34
1789953340 34
1789953345 34
1789953350 34
1789953355 34
1789953360 34
1789953365 29
```
</details>

---

