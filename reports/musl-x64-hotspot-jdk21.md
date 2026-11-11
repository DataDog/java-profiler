---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 15:42:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 9 |
| Allocations | 334 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (5 unique values: 75-83 cores)</summary>

```
1794429413 82
1794429418 77
1794429423 77
1794429428 77
1794429433 77
1794429438 77
1794429443 75
1794429448 75
1794429453 75
1794429458 75
1794429463 75
1794429468 75
1794429473 75
1794429478 75
1794429483 75
1794429488 83
1794429493 83
1794429498 83
1794429503 83
1794429508 83
```
</details>

---

