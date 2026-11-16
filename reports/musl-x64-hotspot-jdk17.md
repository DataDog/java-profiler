---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 15:45:17 EST

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (5 unique values: 37-62 cores)</summary>

```
1794861617 37
1794861622 37
1794861627 62
1794861632 62
1794861637 41
1794861642 41
1794861647 41
1794861652 41
1794861657 41
1794861662 41
1794861667 41
1794861672 41
1794861677 41
1794861682 44
1794861687 44
1794861692 44
1794861697 44
1794861702 46
1794861707 46
1794861712 46
```
</details>

---

