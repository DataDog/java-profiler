---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:06:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 83-92 cores)</summary>

```
1795449632 92
1795449637 92
1795449642 92
1795449647 92
1795449652 92
1795449657 83
1795449662 83
1795449667 85
1795449672 85
1795449677 85
1795449682 85
1795449687 85
1795449692 85
1795449697 85
1795449702 85
1795449707 87
1795449712 87
1795449717 87
1795449722 87
1795449727 87
```
</details>

---

