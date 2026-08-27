---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-27 00:56:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 9 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1787806374 96
1787806379 96
1787806384 88
1787806389 88
1787806394 88
1787806399 88
1787806404 88
1787806409 88
1787806414 88
1787806419 88
1787806424 88
1787806429 88
1787806434 88
1787806439 88
1787806444 88
1787806449 88
1787806454 88
1787806459 88
1787806464 88
1787806469 88
```
</details>

---

