---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-20 11:41:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (3 unique values: 60-63 cores)</summary>

```
1776699071 62
1776699076 62
1776699081 62
1776699086 62
1776699091 62
1776699096 62
1776699101 62
1776699106 62
1776699112 62
1776699117 60
1776699122 60
1776699127 60
1776699132 60
1776699137 62
1776699142 62
1776699147 62
1776699152 62
1776699157 62
1776699162 63
1776699167 63
```
</details>

---

