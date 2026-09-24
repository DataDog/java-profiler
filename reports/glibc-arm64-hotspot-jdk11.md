---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 08:42:46 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790253464 50
1790253469 50
1790253474 50
1790253479 50
1790253484 50
1790253489 50
1790253494 50
1790253499 50
1790253505 50
1790253510 50
1790253515 50
1790253520 50
1790253525 50
1790253530 50
1790253535 50
1790253540 50
1790253545 50
1790253550 50
1790253555 50
1790253560 50
```
</details>

---

