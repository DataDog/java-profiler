---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:25:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 676 |
| Sample Rate | 11.27/sec |
| Health Score | 704% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (4 unique values: 84-96 cores)</summary>

```
1794831580 94
1794831585 94
1794831590 94
1794831595 94
1794831600 96
1794831605 96
1794831610 94
1794831615 94
1794831620 94
1794831625 94
1794831630 94
1794831635 94
1794831640 94
1794831645 94
1794831650 94
1794831655 92
1794831660 92
1794831665 92
1794831670 92
1794831675 92
```
</details>

---

