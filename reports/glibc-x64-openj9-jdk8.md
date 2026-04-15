---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-15 13:00:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 12-15 cores)</summary>

```
1776272238 12
1776272243 12
1776272248 12
1776272253 12
1776272258 15
1776272263 15
1776272268 12
1776272273 12
1776272278 12
1776272283 12
1776272288 12
1776272293 12
1776272298 12
1776272303 12
1776272308 12
1776272313 12
1776272318 12
1776272323 12
1776272328 12
1776272333 12
```
</details>

---

