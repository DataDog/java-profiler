---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 19.40/sec |
| Health Score | 1212% |
| Threads | 9 |
| Allocations | 311 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 811 |
| Sample Rate | 27.03/sec |
| Health Score | 1689% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (3 unique values: 35-43 cores)</summary>

```
1769702698 35
1769702703 37
1769702708 37
1769702713 37
1769702718 37
1769702723 37
1769702728 37
1769702733 37
1769702738 37
1769702743 35
1769702748 35
1769702753 35
1769702758 35
1769702763 35
1769702768 35
1769702773 35
1769702778 35
1769702783 35
1769702788 37
1769702793 37
```
</details>

---

