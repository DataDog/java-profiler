---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-11 11:23:14 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 976 |
| Sample Rate | 16.27/sec |
| Health Score | 1017% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (5 unique values: 76-85 cores)</summary>

```
1778512708 85
1778512713 85
1778512718 85
1778512723 85
1778512728 85
1778512733 85
1778512738 85
1778512743 85
1778512748 85
1778512753 85
1778512758 85
1778512763 85
1778512768 85
1778512773 85
1778512779 85
1778512784 85
1778512789 85
1778512794 85
1778512799 85
1778512804 83
```
</details>

---

