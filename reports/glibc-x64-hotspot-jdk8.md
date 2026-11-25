---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-25 10:02:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1795618623 92
1795618628 92
1795618633 92
1795618638 92
1795618643 92
1795618648 92
1795618653 92
1795618658 92
1795618663 94
1795618668 94
1795618673 94
1795618678 94
1795618683 94
1795618688 94
1795618693 94
1795618698 94
1795618703 94
1795618708 94
1795618713 94
1795618718 94
```
</details>

---

