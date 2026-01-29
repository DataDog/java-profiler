---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-29 08:17:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 19.07/sec |
| Health Score | 1192% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 26.10/sec |
| Health Score | 1631% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 25-30 cores)</summary>

```
1769692265 30
1769692270 30
1769692275 30
1769692280 30
1769692285 30
1769692290 30
1769692295 30
1769692300 30
1769692305 30
1769692310 25
1769692315 25
1769692320 25
1769692325 27
1769692330 27
1769692335 27
1769692340 27
1769692345 27
1769692350 27
1769692355 27
1769692360 27
```
</details>

---

