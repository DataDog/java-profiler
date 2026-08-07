---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 14:42:24 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 51-77 cores)</summary>

```
1786127859 51
1786127864 51
1786127869 51
1786127874 51
1786127879 77
1786127884 77
1786127889 77
1786127894 77
1786127899 77
1786127904 77
1786127909 77
1786127914 75
1786127919 75
1786127924 75
1786127929 75
1786127934 75
1786127939 75
1786127944 75
1786127949 75
1786127954 75
```
</details>

---

