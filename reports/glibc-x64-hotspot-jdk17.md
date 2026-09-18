---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:31:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 11 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (3 unique values: 72-94 cores)</summary>

```
1789737730 72
1789737735 72
1789737740 72
1789737745 72
1789737750 72
1789737755 72
1789737760 72
1789737765 94
1789737770 94
1789737775 94
1789737780 94
1789737785 94
1789737790 94
1789737795 92
1789737800 92
1789737805 92
1789737810 92
1789737815 94
1789737820 94
1789737825 94
```
</details>

---

