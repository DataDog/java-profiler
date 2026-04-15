---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 13:00:39 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 22-48 cores)</summary>

```
1776272225 22
1776272230 22
1776272235 48
1776272240 48
1776272245 48
1776272250 48
1776272255 48
1776272260 48
1776272265 48
1776272270 48
1776272275 48
1776272280 48
1776272285 48
1776272290 48
1776272295 48
1776272300 48
1776272305 48
1776272310 48
1776272315 48
1776272320 48
```
</details>

---

