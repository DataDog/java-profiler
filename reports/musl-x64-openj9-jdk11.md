---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 12:35:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 17-27 cores)</summary>

```
1791908954 27
1791908959 17
1791908964 17
1791908969 17
1791908974 17
1791908979 17
1791908984 17
1791908989 17
1791908994 17
1791908999 27
1791909004 27
1791909009 27
1791909014 27
1791909019 27
1791909024 27
1791909029 27
1791909034 27
1791909039 27
1791909044 27
1791909049 27
```
</details>

---

