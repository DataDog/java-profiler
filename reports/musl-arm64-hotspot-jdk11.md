---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-07 12:48:08 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 10 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1791391418 43
1791391423 43
1791391428 43
1791391433 43
1791391438 43
1791391443 43
1791391448 43
1791391453 43
1791391458 43
1791391463 43
1791391468 43
1791391473 43
1791391478 43
1791391483 43
1791391488 43
1791391493 38
1791391498 38
1791391503 38
1791391508 38
1791391513 38
```
</details>

---

