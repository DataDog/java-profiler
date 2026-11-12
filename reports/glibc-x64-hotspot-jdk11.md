---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 05:38:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 10 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (5 unique values: 69-86 cores)</summary>

```
1794479560 80
1794479566 80
1794479571 80
1794479576 80
1794479581 78
1794479586 78
1794479591 78
1794479596 78
1794479601 78
1794479606 78
1794479611 78
1794479616 78
1794479621 78
1794479626 78
1794479631 82
1794479636 82
1794479641 82
1794479646 82
1794479651 82
1794479656 82
```
</details>

---

