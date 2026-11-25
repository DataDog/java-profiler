---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:02:42 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 8 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 38-48 cores)</summary>

```
1795618598 38
1795618603 38
1795618608 38
1795618613 38
1795618618 48
1795618623 48
1795618628 48
1795618633 48
1795618638 48
1795618643 48
1795618648 48
1795618653 48
1795618658 48
1795618663 48
1795618668 48
1795618673 48
1795618678 48
1795618683 48
1795618688 48
1795618693 48
```
</details>

---

