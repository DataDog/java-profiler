---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-25 11:33:52 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 884 |
| Sample Rate | 14.73/sec |
| Health Score | 921% |
| Threads | 11 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 65-75 cores)</summary>

```
1787671617 73
1787671622 73
1787671627 73
1787671632 73
1787671637 73
1787671642 73
1787671647 73
1787671652 73
1787671657 73
1787671662 73
1787671667 73
1787671672 73
1787671677 73
1787671682 73
1787671687 73
1787671692 75
1787671697 75
1787671702 75
1787671707 75
1787671712 75
```
</details>

---

