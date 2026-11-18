---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:08:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 12 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (2 unique values: 54-60 cores)</summary>

```
1794999795 60
1794999800 60
1794999805 60
1794999810 60
1794999815 60
1794999820 60
1794999825 60
1794999830 60
1794999835 60
1794999840 60
1794999845 60
1794999850 60
1794999855 54
1794999860 54
1794999865 54
1794999870 54
1794999875 54
1794999880 54
1794999885 54
1794999890 54
```
</details>

---

