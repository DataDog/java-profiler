---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 12:35:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 9 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1791908934 30
1791908939 30
1791908944 30
1791908949 30
1791908954 30
1791908959 30
1791908964 30
1791908969 30
1791908974 30
1791908979 30
1791908984 30
1791908989 28
1791908994 28
1791908999 28
1791909004 28
1791909009 30
1791909014 30
1791909019 30
1791909024 30
1791909029 30
```
</details>

---

