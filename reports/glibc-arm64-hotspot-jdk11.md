---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 16:08:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 42-59 cores)</summary>

```
1776974309 42
1776974314 42
1776974319 42
1776974324 42
1776974329 42
1776974334 42
1776974339 42
1776974344 59
1776974349 59
1776974354 59
1776974359 59
1776974364 59
1776974369 59
1776974374 59
1776974379 59
1776974384 59
1776974390 59
1776974395 59
1776974400 59
1776974405 59
```
</details>

---

