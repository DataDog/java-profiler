---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 13:00:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 12 |
| Allocations | 64 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776272252 64
1776272257 64
1776272262 64
1776272267 64
1776272272 64
1776272277 64
1776272282 64
1776272287 64
1776272292 64
1776272297 64
1776272302 64
1776272307 64
1776272313 64
1776272318 64
1776272323 64
1776272328 64
1776272333 64
1776272338 64
1776272343 64
1776272348 64
```
</details>

---

