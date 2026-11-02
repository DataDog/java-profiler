---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:22:54 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 713 |
| Sample Rate | 11.88/sec |
| Health Score | 742% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 68-91 cores)</summary>

```
1793621916 68
1793621921 68
1793621926 68
1793621931 68
1793621936 68
1793621941 68
1793621946 68
1793621951 68
1793621956 68
1793621961 68
1793621966 70
1793621971 70
1793621976 91
1793621981 91
1793621986 91
1793621991 91
1793621996 91
1793622001 91
1793622006 91
1793622011 91
```
</details>

---

