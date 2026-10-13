---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-13 12:35:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 23-30 cores)</summary>

```
1791908964 30
1791908969 30
1791908974 30
1791908979 30
1791908984 30
1791908989 30
1791908994 30
1791908999 30
1791909004 30
1791909009 30
1791909014 30
1791909019 30
1791909024 30
1791909029 28
1791909034 28
1791909039 28
1791909044 28
1791909049 23
1791909054 23
1791909059 23
```
</details>

---

