---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-01-27 10:22:45 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 16.40/sec |
| Health Score | 1025% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 21.20/sec |
| Health Score | 1325% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1769526924 29
1769526929 29
1769526934 29
1769526939 29
1769526944 29
1769526949 29
1769526954 29
1769526959 29
1769526964 29
1769526969 29
1769526974 29
1769526979 29
1769526984 29
1769526989 29
1769526994 29
1769526999 29
1769527004 32
1769527009 32
1769527014 32
1769527019 32
```
</details>

---

