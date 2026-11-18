---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:55:18 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 10 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 54-58 cores)</summary>

```
1795027784 58
1795027789 58
1795027794 58
1795027799 58
1795027804 58
1795027809 58
1795027814 58
1795027819 58
1795027824 58
1795027829 58
1795027834 58
1795027839 58
1795027844 58
1795027849 54
1795027854 54
1795027859 54
1795027864 54
1795027869 54
1795027874 54
1795027879 56
```
</details>

---

