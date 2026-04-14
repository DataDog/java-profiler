---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-14 11:42:11 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 283 |
| Sample Rate | 4.72/sec |
| Health Score | 295% |
| Threads | 11 |
| Allocations | 90 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1776180955 54
1776180960 54
1776180965 54
1776180970 54
1776180976 54
1776180981 54
1776180986 54
1776180991 54
1776180996 54
1776181001 54
1776181006 54
1776181011 54
1776181016 54
1776181021 54
1776181026 54
1776181031 54
1776181036 54
1776181041 54
1776181046 59
1776181051 59
```
</details>

---

