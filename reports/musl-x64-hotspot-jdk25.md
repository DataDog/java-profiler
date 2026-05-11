---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-11 11:23:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (6 unique values: 67-82 cores)</summary>

```
1778512706 82
1778512711 82
1778512716 82
1778512721 82
1778512726 82
1778512731 82
1778512736 82
1778512741 75
1778512746 75
1778512751 75
1778512756 75
1778512761 77
1778512766 77
1778512771 77
1778512776 77
1778512781 77
1778512786 67
1778512791 67
1778512796 69
1778512801 69
```
</details>

---

