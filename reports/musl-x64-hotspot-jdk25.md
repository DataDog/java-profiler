---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-26 01:03:13 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (5 unique values: 62-79 cores)</summary>

```
1790398374 72
1790398379 72
1790398384 76
1790398389 76
1790398394 76
1790398399 76
1790398404 76
1790398409 76
1790398414 76
1790398419 76
1790398424 76
1790398429 76
1790398434 64
1790398439 64
1790398444 64
1790398449 62
1790398454 62
1790398459 62
1790398464 62
1790398469 62
```
</details>

---

