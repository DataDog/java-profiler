---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-28 07:48:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 11 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 11 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793187870 48
1793187875 48
1793187880 48
1793187885 48
1793187890 48
1793187895 48
1793187900 48
1793187905 48
1793187910 48
1793187915 48
1793187920 48
1793187925 48
1793187930 48
1793187935 48
1793187940 48
1793187945 48
1793187950 48
1793187955 43
1793187960 43
1793187965 43
```
</details>

---

