---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 13:02:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 48-54 cores)</summary>

```
1790787379 54
1790787384 54
1790787389 54
1790787394 54
1790787399 54
1790787404 52
1790787409 52
1790787414 48
1790787419 48
1790787424 48
1790787429 48
1790787434 48
1790787439 48
1790787444 48
1790787449 48
1790787454 48
1790787459 48
1790787464 48
1790787469 48
1790787474 48
```
</details>

---

