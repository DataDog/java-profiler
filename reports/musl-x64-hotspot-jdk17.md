---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 48-57 cores)</summary>

```
1795434731 48
1795434736 48
1795434741 48
1795434746 48
1795434751 48
1795434756 48
1795434761 48
1795434766 48
1795434771 50
1795434776 50
1795434781 48
1795434786 48
1795434791 48
1795434796 48
1795434801 48
1795434806 48
1795434811 48
1795434816 48
1795434821 57
1795434826 57
```
</details>

---

