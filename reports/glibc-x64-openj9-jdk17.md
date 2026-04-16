---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-16 10:55:29 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 23-27 cores)</summary>

```
1776351044 27
1776351049 27
1776351054 27
1776351059 27
1776351064 27
1776351069 27
1776351074 27
1776351079 27
1776351084 27
1776351089 27
1776351094 27
1776351099 27
1776351104 27
1776351109 25
1776351114 25
1776351119 25
1776351124 25
1776351129 25
1776351134 25
1776351139 25
```
</details>

---

