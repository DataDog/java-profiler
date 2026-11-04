---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-04 05:47:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 59-73 cores)</summary>

```
1793788899 59
1793788904 59
1793788909 59
1793788914 59
1793788919 71
1793788924 71
1793788929 71
1793788934 73
1793788939 73
1793788944 73
1793788949 73
1793788954 73
1793788959 73
1793788964 72
1793788969 72
1793788974 72
1793788979 72
1793788984 72
1793788989 72
1793788994 72
```
</details>

---

