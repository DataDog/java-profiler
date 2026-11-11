---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:10:51 EST

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
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 19-29 cores)</summary>

```
1794355445 19
1794355450 19
1794355455 19
1794355460 19
1794355465 21
1794355470 21
1794355475 21
1794355480 21
1794355485 21
1794355490 21
1794355495 21
1794355500 21
1794355505 29
1794355510 29
1794355515 21
1794355520 21
1794355525 21
1794355530 21
1794355535 21
1794355540 21
```
</details>

---

