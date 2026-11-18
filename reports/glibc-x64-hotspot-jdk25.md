---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 10:34:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (5 unique values: 50-58 cores)</summary>

```
1795015804 55
1795015809 55
1795015814 55
1795015819 55
1795015824 50
1795015829 50
1795015834 51
1795015839 51
1795015844 51
1795015849 51
1795015854 51
1795015859 51
1795015864 51
1795015869 58
1795015874 58
1795015879 58
1795015884 58
1795015889 58
1795015894 58
1795015899 56
```
</details>

---

