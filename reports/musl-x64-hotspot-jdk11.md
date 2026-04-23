---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 15:46:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 10 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 931 |
| Sample Rate | 15.52/sec |
| Health Score | 970% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 51-86 cores)</summary>

```
1776973272 76
1776973277 76
1776973282 76
1776973287 76
1776973292 80
1776973297 80
1776973302 80
1776973307 80
1776973312 80
1776973317 86
1776973322 86
1776973327 86
1776973332 86
1776973337 86
1776973342 86
1776973347 86
1776973352 86
1776973357 86
1776973362 64
1776973367 64
```
</details>

---

