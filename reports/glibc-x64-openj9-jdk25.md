---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-08 00:56:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 44-64 cores)</summary>

```
1786164789 44
1786164794 44
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
```
</details>

---

