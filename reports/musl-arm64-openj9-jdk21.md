---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 03:59:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1062 |
| Sample Rate | 17.70/sec |
| Health Score | 1106% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791532549 46
1791532554 46
1791532559 46
1791532564 46
1791532569 46
1791532574 46
1791532579 46
1791532584 46
1791532589 46
1791532594 46
1791532599 46
1791532604 51
1791532609 51
1791532614 51
1791532619 51
1791532624 51
1791532629 51
1791532634 51
1791532639 51
1791532644 51
```
</details>

---

