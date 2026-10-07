---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-07 12:48:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 37-48 cores)</summary>

```
1791391367 37
1791391372 37
1791391377 37
1791391382 38
1791391387 38
1791391392 38
1791391398 38
1791391403 38
1791391408 38
1791391413 38
1791391418 38
1791391423 38
1791391428 43
1791391433 43
1791391438 37
1791391443 37
1791391448 37
1791391453 37
1791391458 37
1791391463 37
```
</details>

---

