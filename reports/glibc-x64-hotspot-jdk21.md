---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 07:24:10 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 10 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (5 unique values: 40-90 cores)</summary>

```
1794831570 70
1794831575 70
1794831580 72
1794831585 72
1794831590 72
1794831595 72
1794831600 72
1794831605 72
1794831610 72
1794831615 72
1794831620 90
1794831625 90
1794831630 90
1794831635 57
1794831640 57
1794831645 57
1794831650 57
1794831655 57
1794831660 57
1794831665 40
```
</details>

---

