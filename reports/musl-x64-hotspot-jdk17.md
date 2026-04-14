---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-14 04:48:46 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 310 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 16-21 cores)</summary>

```
1776156300 19
1776156305 19
1776156310 19
1776156315 19
1776156320 19
1776156325 18
1776156330 18
1776156335 18
1776156340 18
1776156345 18
1776156350 18
1776156355 18
1776156360 18
1776156365 18
1776156370 16
1776156375 16
1776156380 18
1776156385 18
1776156390 21
1776156395 21
```
</details>

---

