---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 05:59:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (5 unique values: 51-66 cores)</summary>

```
1794912820 60
1794912825 58
1794912830 58
1794912835 58
1794912840 58
1794912845 58
1794912850 58
1794912855 58
1794912860 58
1794912865 58
1794912870 58
1794912875 51
1794912880 51
1794912885 51
1794912890 56
1794912895 56
1794912900 56
1794912905 56
1794912910 56
1794912915 56
```
</details>

---

