---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 13:30:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
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
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 73-77 cores)</summary>

```
1794334839 73
1794334844 73
1794334849 73
1794334854 73
1794334859 73
1794334864 73
1794334869 73
1794334874 73
1794334879 73
1794334884 73
1794334889 73
1794334894 75
1794334899 75
1794334904 75
1794334909 75
1794334914 75
1794334919 75
1794334924 75
1794334929 75
1794334934 77
```
</details>

---

