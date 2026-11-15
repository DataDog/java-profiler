---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 19:51:05 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (2 unique values: 70-75 cores)</summary>

```
1794703642 70
1794703647 70
1794703652 70
1794703657 70
1794703662 75
1794703667 75
1794703672 75
1794703677 75
1794703682 75
1794703687 75
1794703692 75
1794703697 75
1794703702 75
1794703707 75
1794703712 75
1794703717 75
1794703722 75
1794703727 75
1794703732 75
1794703737 75
```
</details>

---

