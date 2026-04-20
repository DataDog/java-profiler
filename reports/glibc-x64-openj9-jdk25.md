---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 04:41:22 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (7 unique values: 43-79 cores)</summary>

```
1776674145 56
1776674150 79
1776674155 79
1776674160 79
1776674165 79
1776674170 60
1776674175 60
1776674180 60
1776674185 60
1776674190 58
1776674195 58
1776674200 58
1776674205 58
1776674210 58
1776674215 58
1776674220 58
1776674225 58
1776674230 58
1776674235 61
1776674240 61
```
</details>

---

