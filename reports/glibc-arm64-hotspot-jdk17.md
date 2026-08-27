---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-27 00:56:03 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 412 |
| Sample Rate | 6.87/sec |
| Health Score | 429% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 217 |
| Sample Rate | 3.62/sec |
| Health Score | 226% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (4 unique values: 40-48 cores)</summary>

```
1787806374 43
1787806379 43
1787806384 43
1787806389 43
1787806394 43
1787806399 43
1787806404 43
1787806409 43
1787806414 43
1787806419 43
1787806424 43
1787806429 43
1787806434 43
1787806439 43
1787806444 43
1787806449 40
1787806454 40
1787806459 40
1787806464 40
1787806469 40
```
</details>

---

