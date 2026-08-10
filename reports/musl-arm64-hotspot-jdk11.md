---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-10 05:03:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 293 |
| Sample Rate | 4.88/sec |
| Health Score | 305% |
| Threads | 12 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (3 unique values: 24-33 cores)</summary>

```
1786352339 28
1786352344 28
1786352349 28
1786352354 28
1786352359 28
1786352364 28
1786352369 28
1786352374 28
1786352379 28
1786352384 28
1786352389 28
1786352394 33
1786352399 33
1786352404 33
1786352409 33
1786352414 33
1786352419 33
1786352424 24
1786352429 24
1786352434 24
```
</details>

---

