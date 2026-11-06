---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-06 16:49:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 843 |
| Sample Rate | 14.05/sec |
| Health Score | 878% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1794001455 30
1794001460 30
1794001465 30
1794001470 30
1794001475 30
1794001480 30
1794001485 30
1794001490 30
1794001495 30
1794001500 32
1794001505 32
1794001510 29
1794001515 29
1794001520 29
1794001525 29
1794001530 29
1794001536 29
1794001541 29
1794001546 29
1794001551 29
```
</details>

---

