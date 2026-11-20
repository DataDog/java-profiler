---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-20 05:51:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 62-86 cores)</summary>

```
1795171633 83
1795171638 83
1795171643 83
1795171648 83
1795171653 83
1795171658 83
1795171663 83
1795171668 83
1795171673 83
1795171678 83
1795171683 83
1795171688 83
1795171693 83
1795171698 83
1795171703 86
1795171708 86
1795171713 86
1795171718 86
1795171723 86
1795171728 86
```
</details>

---

