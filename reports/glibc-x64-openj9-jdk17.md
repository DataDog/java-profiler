---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 13:00:39 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (6 unique values: 68-78 cores)</summary>

```
1776272226 73
1776272231 73
1776272236 68
1776272241 68
1776272246 72
1776272251 72
1776272256 72
1776272261 75
1776272266 75
1776272271 75
1776272276 75
1776272281 75
1776272286 75
1776272291 75
1776272296 78
1776272301 78
1776272306 78
1776272311 78
1776272316 75
1776272321 75
```
</details>

---

