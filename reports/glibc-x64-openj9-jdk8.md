---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-11 16:04:54 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 23-29 cores)</summary>

```
1794430826 29
1794430831 29
1794430836 29
1794430841 29
1794430846 29
1794430851 29
1794430856 29
1794430861 29
1794430866 23
1794430871 23
1794430876 23
1794430881 23
1794430886 23
1794430891 23
1794430896 23
1794430901 23
1794430906 23
1794430911 23
1794430916 23
1794430921 23
```
</details>

---

