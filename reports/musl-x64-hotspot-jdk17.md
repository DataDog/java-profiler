---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-27 14:34:08 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 54-87 cores)</summary>

```
1777314543 54
1777314548 54
1777314553 78
1777314558 78
1777314563 78
1777314568 82
1777314573 82
1777314578 82
1777314583 82
1777314588 82
1777314593 82
1777314598 82
1777314603 82
1777314608 82
1777314613 82
1777314618 87
1777314623 87
1777314628 87
1777314633 87
1777314638 87
```
</details>

---

