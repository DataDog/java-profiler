---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:08:13 EST

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 65-86 cores)</summary>

```
1794567768 84
1794567773 84
1794567778 84
1794567783 86
1794567788 86
1794567793 84
1794567798 84
1794567803 79
1794567808 79
1794567813 79
1794567818 81
1794567823 81
1794567828 65
1794567833 65
1794567838 65
1794567843 65
1794567848 65
1794567853 65
1794567858 65
1794567863 65
```
</details>

---

