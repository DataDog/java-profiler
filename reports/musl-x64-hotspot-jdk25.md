---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-30 10:04:41 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 902 |
| Sample Rate | 15.03/sec |
| Health Score | 939% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 81-86 cores)</summary>

```
1777557335 83
1777557340 83
1777557345 85
1777557350 85
1777557355 85
1777557360 85
1777557365 85
1777557370 85
1777557375 85
1777557380 85
1777557385 85
1777557390 85
1777557395 85
1777557400 85
1777557405 85
1777557410 85
1777557415 81
1777557420 81
1777557425 81
1777557430 81
```
</details>

---

