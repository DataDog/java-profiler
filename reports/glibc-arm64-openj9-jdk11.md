---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 19:04:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 7 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 10 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1793141958 34
1793141963 34
1793141968 34
1793141973 34
1793141978 34
1793141983 34
1793141988 34
1793141993 34
1793141998 34
1793142003 34
1793142008 34
1793142013 34
1793142018 34
1793142023 34
1793142028 34
1793142033 34
1793142038 34
1793142043 32
1793142048 32
1793142053 32
```
</details>

---

