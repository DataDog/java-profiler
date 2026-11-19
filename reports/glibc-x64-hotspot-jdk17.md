---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 05:09:42 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (5 unique values: 34-47 cores)</summary>

```
1795082641 45
1795082646 45
1795082651 45
1795082656 45
1795082661 45
1795082666 45
1795082671 45
1795082676 45
1795082681 47
1795082686 47
1795082691 47
1795082696 47
1795082701 38
1795082706 38
1795082711 38
1795082716 38
1795082721 38
1795082726 38
1795082731 36
1795082736 36
```
</details>

---

