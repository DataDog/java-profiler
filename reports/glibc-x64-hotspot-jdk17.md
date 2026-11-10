---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 09:12:47 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (3 unique values: 50-57 cores)</summary>

```
1794319691 52
1794319696 52
1794319701 52
1794319706 52
1794319711 52
1794319716 52
1794319721 50
1794319726 50
1794319731 50
1794319736 50
1794319741 50
1794319746 50
1794319751 50
1794319756 50
1794319761 50
1794319766 50
1794319771 50
1794319776 57
1794319782 57
1794319787 57
```
</details>

---

