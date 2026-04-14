---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-14 11:42:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (6 unique values: 76-83 cores)</summary>

```
1776180927 83
1776180932 83
1776180937 83
1776180942 83
1776180947 79
1776180952 79
1776180957 79
1776180962 77
1776180967 77
1776180972 77
1776180977 77
1776180982 79
1776180987 79
1776180992 79
1776180997 82
1776181002 82
1776181007 82
1776181012 82
1776181017 82
1776181022 78
```
</details>

---

