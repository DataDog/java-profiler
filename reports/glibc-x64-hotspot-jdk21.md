---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:04:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 10 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 822 |
| Sample Rate | 13.70/sec |
| Health Score | 856% |
| Threads | 13 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (4 unique values: 84-89 cores)</summary>

```
1770825606 89
1770825611 89
1770825616 89
1770825621 89
1770825626 89
1770825631 89
1770825636 84
1770825641 84
1770825646 84
1770825651 86
1770825656 86
1770825661 86
1770825666 86
1770825671 86
1770825676 86
1770825681 86
1770825686 86
1770825691 86
1770825696 86
1770825701 86
```
</details>

---

