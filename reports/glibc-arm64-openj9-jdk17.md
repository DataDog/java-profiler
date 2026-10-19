---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 07:26:48 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792408955 43
1792408960 43
1792408965 43
1792408970 43
1792408975 43
1792408980 43
1792408985 43
1792408990 43
1792408995 43
1792409000 48
1792409005 48
1792409010 43
1792409015 43
1792409020 43
1792409025 43
1792409030 43
1792409035 43
1792409040 43
1792409045 43
1792409050 43
```
</details>

---

