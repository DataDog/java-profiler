---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 16:39:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 966 |
| Sample Rate | 16.10/sec |
| Health Score | 1006% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794346388 36
1794346393 36
1794346398 36
1794346403 36
1794346408 36
1794346413 36
1794346418 36
1794346423 36
1794346428 36
1794346433 36
1794346438 36
1794346443 36
1794346448 36
1794346453 36
1794346458 36
1794346463 36
1794346468 36
1794346473 36
1794346478 36
1794346483 36
```
</details>

---

