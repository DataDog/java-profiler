---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 11:31:58 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 410 |
| Sample Rate | 6.83/sec |
| Health Score | 427% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 19-23 cores)</summary>

```
1776871167 23
1776871172 23
1776871177 23
1776871182 23
1776871187 23
1776871192 21
1776871197 21
1776871202 21
1776871207 21
1776871212 19
1776871217 19
1776871222 21
1776871227 21
1776871232 21
1776871237 21
1776871242 21
1776871247 21
1776871252 21
1776871257 21
1776871262 23
```
</details>

---

