---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:47:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 39-41 cores)</summary>

```
1793788894 39
1793788899 39
1793788904 39
1793788909 39
1793788914 41
1793788919 41
1793788924 41
1793788929 41
1793788934 41
1793788939 41
1793788944 41
1793788949 41
1793788954 41
1793788959 41
1793788964 41
1793788969 41
1793788974 41
1793788979 41
1793788984 41
1793788989 41
```
</details>

---

