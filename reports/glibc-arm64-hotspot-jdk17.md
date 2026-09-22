---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-22 11:47:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 47-49 cores)</summary>

```
1790091686 48
1790091691 48
1790091696 48
1790091701 48
1790091706 47
1790091711 47
1790091716 47
1790091721 47
1790091726 47
1790091731 47
1790091736 47
1790091741 47
1790091746 47
1790091751 47
1790091756 47
1790091761 47
1790091766 47
1790091771 47
1790091776 47
1790091781 49
```
</details>

---

