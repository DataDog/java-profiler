---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:59:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1791532539 48
1791532544 48
1791532549 48
1791532554 48
1791532559 48
1791532564 48
1791532569 48
1791532574 48
1791532579 48
1791532584 48
1791532589 48
1791532594 43
1791532599 43
1791532604 43
1791532609 43
1791532614 43
1791532619 43
1791532624 38
1791532629 38
1791532634 38
```
</details>

---

