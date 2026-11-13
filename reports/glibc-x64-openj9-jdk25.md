---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 11:44:54 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1794587967 68
1794587972 68
1794587977 68
1794587982 68
1794587987 68
1794587992 68
1794587997 68
1794588002 68
1794588007 68
1794588012 68
1794588017 68
1794588022 68
1794588027 64
1794588032 64
1794588037 64
1794588042 64
1794588047 64
1794588052 64
1794588057 65
1794588062 65
```
</details>

---

