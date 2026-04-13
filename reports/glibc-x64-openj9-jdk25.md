---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-12 21:18:53 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1776042885 30
1776042890 30
1776042895 30
1776042900 27
1776042905 27
1776042910 27
1776042915 27
1776042920 27
1776042925 27
1776042930 27
1776042935 27
1776042940 27
1776042945 27
1776042950 27
1776042955 27
1776042960 27
1776042965 27
1776042970 27
1776042975 27
1776042980 27
```
</details>

---

