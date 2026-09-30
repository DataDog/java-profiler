---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 08:37:23 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 82-94 cores)</summary>

```
1790771553 94
1790771558 94
1790771563 92
1790771568 92
1790771573 90
1790771578 90
1790771583 90
1790771588 90
1790771593 90
1790771598 90
1790771603 90
1790771608 90
1790771613 90
1790771618 82
1790771623 82
1790771628 82
1790771633 82
1790771638 82
1790771643 82
1790771648 82
```
</details>

---

