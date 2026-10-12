---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-12 03:21:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791789380 40
1791789385 40
1791789390 40
1791789395 40
1791789400 40
1791789405 40
1791789410 40
1791789415 40
1791789420 40
1791789425 40
1791789430 40
1791789435 40
1791789440 40
1791789445 40
1791789450 40
1791789455 40
1791789460 40
1791789465 40
1791789470 40
1791789475 40
```
</details>

---

