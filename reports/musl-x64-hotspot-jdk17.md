---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 13:55:20 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 692 |
| Sample Rate | 11.53/sec |
| Health Score | 721% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (6 unique values: 74-81 cores)</summary>

```
1795027784 77
1795027789 77
1795027794 77
1795027799 79
1795027804 79
1795027809 79
1795027814 79
1795027819 79
1795027824 79
1795027829 79
1795027834 79
1795027839 79
1795027844 79
1795027849 79
1795027854 79
1795027859 81
1795027864 81
1795027869 81
1795027874 76
1795027879 76
```
</details>

---

