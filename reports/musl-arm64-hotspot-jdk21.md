---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 14:48:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 38 |
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
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 322 |
| Sample Rate | 5.37/sec |
| Health Score | 336% |
| Threads | 14 |
| Allocations | 182 |

<details>
<summary>CPU Timeline (3 unique values: 34-39 cores)</summary>

```
1794253470 39
1794253475 39
1794253480 39
1794253485 39
1794253490 39
1794253495 39
1794253500 39
1794253505 39
1794253511 39
1794253516 39
1794253521 39
1794253526 39
1794253531 39
1794253536 39
1794253541 39
1794253546 39
1794253551 34
1794253556 34
1794253561 38
1794253566 38
```
</details>

---

