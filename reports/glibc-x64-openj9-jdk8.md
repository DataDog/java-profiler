---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 07:51:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 332 |
| Sample Rate | 5.53/sec |
| Health Score | 346% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 73-96 cores)</summary>

```
1795610790 73
1795610795 73
1795610800 73
1795610805 96
1795610810 96
1795610815 96
1795610820 77
1795610825 77
1795610830 77
1795610835 77
1795610840 77
1795610845 77
1795610850 77
1795610855 77
1795610860 77
1795610865 77
1795610870 77
1795610875 77
1795610880 77
1795610885 77
```
</details>

---

