---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 06:01:49 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 433 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 727 |
| Sample Rate | 12.12/sec |
| Health Score | 757% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 71-79 cores)</summary>

```
1794567318 77
1794567323 77
1794567328 77
1794567333 77
1794567338 79
1794567343 79
1794567348 79
1794567353 79
1794567358 79
1794567363 79
1794567368 79
1794567373 79
1794567378 79
1794567383 79
1794567388 79
1794567393 79
1794567398 79
1794567403 79
1794567408 79
1794567413 79
```
</details>

---

