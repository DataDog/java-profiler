---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 07:10:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 36 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 13 |
| Allocations | 189 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776337240 64
1776337245 64
1776337250 64
1776337255 64
1776337260 64
1776337265 64
1776337270 64
1776337275 64
1776337280 64
1776337285 64
1776337290 64
1776337295 64
1776337300 64
1776337305 64
1776337310 59
1776337315 59
1776337320 59
1776337325 59
1776337330 64
1776337335 64
```
</details>

---

