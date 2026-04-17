---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-17 10:21:31 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 878 |
| Sample Rate | 14.63/sec |
| Health Score | 914% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 80-83 cores)</summary>

```
1776435124 80
1776435129 80
1776435134 80
1776435139 80
1776435144 83
1776435149 83
1776435154 83
1776435159 83
1776435164 83
1776435169 83
1776435174 83
1776435179 81
1776435184 81
1776435189 81
1776435194 81
1776435199 81
1776435204 81
1776435209 81
1776435214 83
1776435219 83
```
</details>

---

