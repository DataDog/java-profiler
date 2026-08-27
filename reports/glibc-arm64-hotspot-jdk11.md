---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-27 00:56:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 12 |
| Allocations | 186 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787806369 48
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
1787806434 48
1787806439 48
1787806444 48
1787806449 48
1787806454 48
1787806459 48
1787806464 48
```
</details>

---

