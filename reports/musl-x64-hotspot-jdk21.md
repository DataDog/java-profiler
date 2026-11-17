---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 12:52:32 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (4 unique values: 80-87 cores)</summary>

```
1794937490 85
1794937495 85
1794937500 85
1794937505 85
1794937510 85
1794937515 85
1794937520 85
1794937525 85
1794937530 85
1794937535 87
1794937540 87
1794937545 87
1794937550 87
1794937555 87
1794937560 87
1794937565 87
1794937570 87
1794937575 87
1794937580 82
1794937585 82
```
</details>

---

