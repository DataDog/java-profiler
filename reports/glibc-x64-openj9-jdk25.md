---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 07:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1793621931 59
1793621936 59
1793621941 59
1793621946 59
1793621951 59
1793621956 59
1793621961 59
1793621966 59
1793621971 59
1793621976 59
1793621981 59
1793621986 59
1793621991 59
1793621996 64
1793622001 64
1793622006 64
1793622011 64
1793622016 64
1793622021 64
1793622026 64
```
</details>

---

