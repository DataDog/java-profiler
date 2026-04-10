---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-10 14:16:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 883 |
| Sample Rate | 14.72/sec |
| Health Score | 920% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 78-83 cores)</summary>

```
1775844588 78
1775844593 78
1775844598 78
1775844603 78
1775844608 81
1775844613 81
1775844618 81
1775844623 81
1775844628 83
1775844633 83
1775844638 83
1775844643 83
1775844648 83
1775844653 83
1775844658 83
1775844663 83
1775844668 83
1775844673 83
1775844678 83
1775844683 83
```
</details>

---

