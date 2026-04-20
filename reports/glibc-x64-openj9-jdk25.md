---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-20 07:58:13 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1776686114 64
1776686119 64
1776686124 64
1776686129 64
1776686134 60
1776686139 60
1776686144 60
1776686149 60
1776686154 60
1776686159 60
1776686164 60
1776686169 60
1776686174 60
1776686179 60
1776686184 60
1776686189 60
1776686194 60
1776686199 60
1776686204 60
1776686209 60
```
</details>

---

