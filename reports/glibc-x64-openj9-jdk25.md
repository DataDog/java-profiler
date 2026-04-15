---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 13:00:40 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 67-71 cores)</summary>

```
1776272230 71
1776272235 71
1776272240 71
1776272245 71
1776272250 71
1776272255 71
1776272260 71
1776272265 71
1776272270 71
1776272275 71
1776272280 71
1776272285 71
1776272290 71
1776272295 71
1776272300 67
1776272305 67
1776272310 67
1776272315 67
1776272320 67
1776272325 67
```
</details>

---

