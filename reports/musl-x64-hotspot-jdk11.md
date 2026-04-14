---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-14 04:48:46 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 908 |
| Sample Rate | 15.13/sec |
| Health Score | 946% |
| Threads | 10 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 22-29 cores)</summary>

```
1776156316 24
1776156321 24
1776156326 22
1776156331 22
1776156336 24
1776156341 24
1776156346 24
1776156351 29
1776156356 29
1776156361 29
1776156366 29
1776156371 29
1776156376 29
1776156381 29
1776156386 29
1776156391 29
1776156396 29
1776156401 29
1776156406 29
1776156411 29
```
</details>

---

