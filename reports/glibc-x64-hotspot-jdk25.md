---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 07:51:08 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 73-96 cores)</summary>

```
1795610784 73
1795610789 73
1795610794 73
1795610799 73
1795610804 73
1795610809 96
1795610814 96
1795610819 77
1795610824 77
1795610829 77
1795610834 77
1795610839 77
1795610844 77
1795610849 77
1795610854 77
1795610859 77
1795610864 77
1795610869 77
1795610874 77
1795610879 77
```
</details>

---

