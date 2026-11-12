---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:21:26 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 59-74 cores)</summary>

```
1794507317 61
1794507322 61
1794507327 61
1794507332 61
1794507337 61
1794507342 61
1794507347 61
1794507352 61
1794507357 61
1794507362 61
1794507367 61
1794507372 59
1794507377 59
1794507382 59
1794507387 59
1794507392 59
1794507397 59
1794507402 59
1794507408 59
1794507413 59
```
</details>

---

