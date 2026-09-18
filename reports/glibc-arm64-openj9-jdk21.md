---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 10:38:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1789741924 47
1789741929 47
1789741934 47
1789741939 47
1789741944 47
1789741949 47
1789741954 47
1789741959 47
1789741964 47
1789741969 47
1789741974 47
1789741979 48
1789741984 48
1789741989 48
1789741994 48
1789741999 48
1789742004 48
1789742009 48
1789742014 48
1789742019 48
```
</details>

---

