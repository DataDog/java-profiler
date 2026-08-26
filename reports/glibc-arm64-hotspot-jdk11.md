---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 10:30:25 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 12 |
| Allocations | 189 |

<details>
<summary>CPU Timeline (6 unique values: 39-44 cores)</summary>

```
1787754369 39
1787754374 39
1787754379 39
1787754384 39
1787754389 39
1787754394 44
1787754399 44
1787754404 44
1787754409 41
1787754414 41
1787754419 40
1787754424 40
1787754429 42
1787754434 42
1787754439 42
1787754444 42
1787754449 42
1787754454 42
1787754459 42
1787754464 42
```
</details>

---

