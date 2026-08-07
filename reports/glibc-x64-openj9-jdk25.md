---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 05:50:44 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (3 unique values: 66-70 cores)</summary>

```
1786095965 68
1786095970 68
1786095975 68
1786095980 68
1786095985 68
1786095990 68
1786095995 70
1786096000 70
1786096005 70
1786096010 70
1786096015 70
1786096020 66
1786096025 66
1786096030 66
1786096035 66
1786096040 66
1786096045 66
1786096050 66
1786096055 66
1786096060 66
```
</details>

---

