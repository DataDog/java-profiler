---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:21:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 14 |
| Allocations | 130 |

<details>
<summary>CPU Timeline (3 unique values: 39-51 cores)</summary>

```
1794507433 39
1794507438 39
1794507443 39
1794507448 39
1794507453 39
1794507458 51
1794507463 51
1794507468 51
1794507473 51
1794507478 51
1794507483 43
1794507488 43
1794507493 43
1794507498 43
1794507503 43
1794507508 43
1794507513 43
1794507518 43
1794507523 43
1794507528 43
```
</details>

---

