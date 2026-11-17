---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 07:23:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 356 |
| Sample Rate | 5.93/sec |
| Health Score | 371% |
| Threads | 12 |
| Allocations | 177 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 15-51 cores)</summary>

```
1794917989 15
1794917994 15
1794917999 15
1794918004 15
1794918009 15
1794918014 15
1794918019 15
1794918024 15
1794918029 15
1794918034 15
1794918039 15
1794918044 15
1794918049 15
1794918054 51
1794918059 51
1794918064 51
1794918069 51
1794918074 51
1794918079 51
1794918084 51
```
</details>

---

