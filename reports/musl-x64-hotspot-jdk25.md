---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 14:28:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (5 unique values: 80-89 cores)</summary>

```
1776277345 82
1776277350 82
1776277355 80
1776277360 80
1776277365 82
1776277370 82
1776277375 82
1776277380 85
1776277385 85
1776277390 85
1776277395 85
1776277400 85
1776277405 85
1776277410 85
1776277415 85
1776277420 85
1776277425 87
1776277430 87
1776277435 89
1776277440 89
```
</details>

---

