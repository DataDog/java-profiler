---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 16:06:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (5 unique values: 75-92 cores)</summary>

```
1794430818 75
1794430823 77
1794430828 77
1794430833 77
1794430838 77
1794430843 77
1794430848 77
1794430853 77
1794430858 77
1794430863 91
1794430868 91
1794430873 91
1794430878 89
1794430883 89
1794430888 92
1794430893 92
1794430898 92
1794430903 92
1794430908 92
1794430913 92
```
</details>

---

