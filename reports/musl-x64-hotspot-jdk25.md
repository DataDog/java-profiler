---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 10:53:47 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 8 |
| Allocations | 457 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1794498336 29
1794498341 29
1794498346 29
1794498351 29
1794498356 29
1794498361 29
1794498366 29
1794498371 29
1794498376 19
1794498381 19
1794498386 19
1794498391 19
1794498396 19
1794498401 19
1794498406 19
1794498411 19
1794498416 29
1794498421 29
1794498426 27
1794498431 27
```
</details>

---

