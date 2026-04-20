---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-20 10:34:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 11 |
| Allocations | 420 |

<details>
<summary>CPU Timeline (5 unique values: 83-89 cores)</summary>

```
1776695379 85
1776695384 85
1776695389 85
1776695394 85
1776695399 85
1776695404 85
1776695409 85
1776695414 85
1776695419 85
1776695424 83
1776695429 83
1776695434 83
1776695439 87
1776695444 87
1776695449 87
1776695454 89
1776695459 89
1776695464 89
1776695469 89
1776695474 88
```
</details>

---

