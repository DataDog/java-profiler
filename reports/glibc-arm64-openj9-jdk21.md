---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 16:08:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 80 |

<details>
<summary>CPU Timeline (2 unique values: 43-60 cores)</summary>

```
1776974294 60
1776974299 60
1776974304 60
1776974309 60
1776974314 60
1776974319 60
1776974324 60
1776974329 60
1776974334 60
1776974340 60
1776974345 60
1776974350 43
1776974355 43
1776974360 60
1776974365 60
1776974370 60
1776974375 60
1776974380 60
1776974385 60
1776974390 60
```
</details>

---

