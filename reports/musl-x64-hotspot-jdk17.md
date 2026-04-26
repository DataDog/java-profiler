---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-26 16:34:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
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
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 8 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1777235379 32
1777235384 32
1777235389 32
1777235394 32
1777235399 32
1777235404 32
1777235410 32
1777235415 32
1777235420 32
1777235425 32
1777235430 32
1777235435 30
1777235440 30
1777235445 30
1777235450 30
1777235455 30
1777235460 30
1777235465 32
1777235470 32
1777235475 30
```
</details>

---

