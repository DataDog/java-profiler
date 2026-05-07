---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 19:05:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 13 |
| Allocations | 156 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778194854 64
1778194859 64
1778194864 64
1778194869 64
1778194874 64
1778194879 64
1778194884 59
1778194889 59
1778194894 59
1778194899 59
1778194904 59
1778194909 59
1778194914 59
1778194919 59
1778194924 59
1778194929 59
1778194934 59
1778194939 59
1778194944 59
1778194949 59
```
</details>

---

