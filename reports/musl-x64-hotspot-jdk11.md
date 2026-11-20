---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 07:26:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 568 |

<details>
<summary>CPU Timeline (3 unique values: 10-30 cores)</summary>

```
1795177335 28
1795177340 28
1795177345 28
1795177350 28
1795177355 28
1795177360 30
1795177365 30
1795177370 30
1795177375 30
1795177380 30
1795177385 30
1795177390 30
1795177395 30
1795177400 28
1795177405 28
1795177410 28
1795177415 28
1795177420 28
1795177425 28
1795177430 28
```
</details>

---

