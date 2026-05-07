---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 09:00:16 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 788 |
| Sample Rate | 13.13/sec |
| Health Score | 821% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 35-50 cores)</summary>

```
1778158379 35
1778158384 35
1778158389 35
1778158394 35
1778158399 35
1778158404 35
1778158409 35
1778158414 35
1778158419 35
1778158424 35
1778158429 35
1778158434 35
1778158439 35
1778158444 35
1778158449 40
1778158454 40
1778158459 40
1778158464 40
1778158469 40
1778158474 50
```
</details>

---

