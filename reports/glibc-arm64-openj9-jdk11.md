---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 05:58:41 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 11 |
| Allocations | 149 |

<details>
<summary>CPU Timeline (2 unique values: 31-36 cores)</summary>

```
1794307957 31
1794307963 31
1794307968 31
1794307973 31
1794307978 31
1794307983 31
1794307988 31
1794307993 31
1794307998 31
1794308003 31
1794308008 31
1794308013 31
1794308018 31
1794308023 31
1794308028 31
1794308033 31
1794308038 31
1794308043 31
1794308048 31
1794308053 31
```
</details>

---

