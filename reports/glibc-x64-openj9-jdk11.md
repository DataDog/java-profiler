---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 10:38:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789741904 94
1789741909 94
1789741914 96
1789741919 96
1789741924 96
1789741929 96
1789741934 96
1789741939 96
1789741944 96
1789741949 96
1789741954 96
1789741959 96
1789741964 96
1789741969 96
1789741974 96
1789741979 96
1789741984 96
1789741989 96
1789741994 96
1789741999 96
```
</details>

---

