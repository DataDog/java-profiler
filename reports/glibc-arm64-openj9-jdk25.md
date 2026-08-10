---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-10 05:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 11 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (4 unique values: 31-44 cores)</summary>

```
1786354978 34
1786354983 34
1786354988 34
1786354993 34
1786354998 34
1786355003 34
1786355008 34
1786355013 34
1786355018 34
1786355023 34
1786355028 39
1786355033 39
1786355038 39
1786355043 39
1786355048 39
1786355053 39
1786355058 39
1786355063 39
1786355068 44
1786355073 44
```
</details>

---

