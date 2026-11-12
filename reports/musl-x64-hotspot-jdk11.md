---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 12:48:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (4 unique values: 70-82 cores)</summary>

```
1794505455 70
1794505460 70
1794505465 70
1794505470 70
1794505475 70
1794505480 70
1794505485 70
1794505490 70
1794505495 70
1794505500 70
1794505505 70
1794505510 70
1794505515 70
1794505520 78
1794505525 78
1794505530 78
1794505535 78
1794505540 78
1794505545 78
1794505550 80
```
</details>

---

