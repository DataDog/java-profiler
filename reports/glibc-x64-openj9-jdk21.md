---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-21 06:58:13 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1007 |
| Sample Rate | 16.78/sec |
| Health Score | 1049% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 87-91 cores)</summary>

```
1776768917 87
1776768922 87
1776768927 87
1776768932 87
1776768937 91
1776768942 91
1776768947 91
1776768952 91
1776768957 91
1776768962 91
1776768967 91
1776768972 91
1776768977 91
1776768982 91
1776768987 91
1776768992 91
1776768997 91
1776769002 91
1776769007 91
1776769012 91
```
</details>

---

