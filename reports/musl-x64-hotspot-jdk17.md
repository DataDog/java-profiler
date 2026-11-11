---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 10:44:48 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 86 |
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
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 10 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 84-88 cores)</summary>

```
1794411574 84
1794411579 84
1794411584 84
1794411589 84
1794411594 84
1794411599 84
1794411604 84
1794411609 84
1794411614 88
1794411619 88
1794411624 88
1794411629 88
1794411634 88
1794411639 88
1794411644 88
1794411649 88
1794411654 88
1794411659 88
1794411664 88
1794411669 88
```
</details>

---

