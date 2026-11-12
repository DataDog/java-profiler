---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:38:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (5 unique values: 85-92 cores)</summary>

```
1794479568 85
1794479573 88
1794479578 88
1794479583 88
1794479588 88
1794479593 88
1794479598 88
1794479603 88
1794479608 92
1794479613 92
1794479618 92
1794479623 92
1794479628 92
1794479633 92
1794479638 92
1794479643 92
1794479648 92
1794479653 90
1794479658 90
1794479663 88
```
</details>

---

