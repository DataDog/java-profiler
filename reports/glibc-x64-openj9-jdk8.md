---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-13 12:35:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 179 |
| Sample Rate | 2.98/sec |
| Health Score | 186% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1791908919 30
1791908924 30
1791908929 30
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
```
</details>

---

