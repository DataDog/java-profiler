---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 17:37:33 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 9 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (2 unique values: 46-68 cores)</summary>

```
1794782016 46
1794782021 46
1794782026 46
1794782031 46
1794782036 46
1794782041 46
1794782046 46
1794782051 46
1794782056 68
1794782061 68
1794782066 68
1794782071 68
1794782076 68
1794782081 68
1794782086 68
1794782091 68
1794782096 68
1794782101 68
1794782106 68
1794782111 68
```
</details>

---

