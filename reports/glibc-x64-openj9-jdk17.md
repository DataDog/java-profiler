---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 04:41:21 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (6 unique values: 24-36 cores)</summary>

```
1776674162 36
1776674167 36
1776674172 36
1776674177 32
1776674182 32
1776674187 30
1776674192 30
1776674197 30
1776674202 30
1776674207 30
1776674212 30
1776674217 30
1776674222 30
1776674227 24
1776674232 24
1776674238 25
1776674243 25
1776674248 25
1776674253 25
1776674258 25
```
</details>

---

