---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-27 10:38:59 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 17-59 cores)</summary>

```
1795793661 17
1795793666 17
1795793671 17
1795793676 17
1795793681 17
1795793686 17
1795793691 17
1795793696 17
1795793701 40
1795793706 40
1795793711 40
1795793716 40
1795793721 40
1795793726 40
1795793731 40
1795793736 40
1795793741 59
1795793746 59
1795793751 59
1795793756 59
```
</details>

---

