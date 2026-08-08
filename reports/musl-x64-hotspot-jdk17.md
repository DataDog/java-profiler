---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-08 00:57:01 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 559 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1786164799 44
1786164804 44
1786164809 44
1786164814 44
1786164819 44
1786164824 44
1786164829 44
1786164834 44
1786164839 44
1786164844 44
1786164849 44
1786164854 44
1786164859 44
1786164864 44
1786164869 44
1786164874 44
1786164879 44
1786164884 64
1786164889 64
1786164894 64
```
</details>

---

