---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 13:30:51 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 79-91 cores)</summary>

```
1794334829 91
1794334834 91
1794334839 87
1794334844 87
1794334849 87
1794334854 87
1794334859 87
1794334864 87
1794334869 87
1794334874 81
1794334879 81
1794334884 81
1794334889 81
1794334894 79
1794334899 79
1794334904 79
1794334909 79
1794334914 79
1794334919 79
1794334924 81
```
</details>

---

