---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 09:32:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (5 unique values: 37-48 cores)</summary>

```
1787232399 48
1787232404 48
1787232409 48
1787232414 48
1787232419 48
1787232424 48
1787232429 48
1787232434 48
1787232439 46
1787232444 46
1787232449 46
1787232454 46
1787232459 45
1787232464 45
1787232469 45
1787232474 45
1787232479 45
1787232484 45
1787232489 37
1787232494 37
```
</details>

---

