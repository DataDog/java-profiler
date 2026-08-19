---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 10:53:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (4 unique values: 73-81 cores)</summary>

```
1787150944 81
1787150949 77
1787150954 77
1787150959 77
1787150964 77
1787150969 77
1787150974 77
1787150979 79
1787150984 79
1787150989 79
1787150994 79
1787150999 79
1787151004 79
1787151009 79
1787151014 79
1787151019 79
1787151024 79
1787151029 73
1787151034 73
1787151039 73
```
</details>

---

