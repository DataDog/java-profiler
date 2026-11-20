---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 16:44:20 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 53 |
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
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 53-58 cores)</summary>

```
1795210744 58
1795210749 58
1795210754 58
1795210759 58
1795210764 58
1795210769 58
1795210774 58
1795210779 58
1795210784 58
1795210789 56
1795210794 56
1795210799 56
1795210804 56
1795210809 56
1795210814 56
1795210819 56
1795210824 56
1795210829 56
1795210834 56
1795210839 53
```
</details>

---

