---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-22 12:02:58 EDT

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
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 9 |
| Allocations | 428 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 80-82 cores)</summary>

```
1776873343 82
1776873348 82
1776873353 82
1776873358 82
1776873363 82
1776873368 82
1776873373 82
1776873378 82
1776873383 82
1776873388 82
1776873393 82
1776873398 82
1776873403 82
1776873408 82
1776873413 82
1776873418 82
1776873423 82
1776873428 82
1776873433 82
1776873438 80
```
</details>

---

