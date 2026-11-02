---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 17:11:47 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 741 |
| Sample Rate | 12.35/sec |
| Health Score | 772% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1793656894 73
1793656899 73
1793656904 73
1793656909 73
1793656914 73
1793656919 73
1793656924 73
1793656929 73
1793656934 73
1793656939 73
1793656944 71
1793656949 71
1793656954 71
1793656959 71
1793656964 71
1793656969 73
1793656974 73
1793656979 73
1793656984 73
1793656989 73
```
</details>

---

