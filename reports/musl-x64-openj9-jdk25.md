---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 20:59:13 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 440 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 37-44 cores)</summary>

```
1793148889 37
1793148894 39
1793148899 39
1793148904 44
1793148909 44
1793148914 44
1793148919 44
1793148924 44
1793148929 44
1793148934 44
1793148939 44
1793148944 44
1793148949 44
1793148954 44
1793148959 44
1793148964 44
1793148969 44
1793148974 44
1793148979 44
1793148984 42
```
</details>

---

