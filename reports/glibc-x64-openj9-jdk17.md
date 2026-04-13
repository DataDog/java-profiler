---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-12 21:18:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1776042881 28
1776042886 28
1776042891 28
1776042896 28
1776042901 28
1776042906 28
1776042911 28
1776042916 28
1776042921 32
1776042926 32
1776042931 32
1776042936 32
1776042941 32
1776042946 32
1776042951 32
1776042956 32
1776042961 32
1776042966 32
1776042971 32
1776042976 32
```
</details>

---

