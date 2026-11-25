---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:36:31 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 8 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (3 unique values: 49-52 cores)</summary>

```
1795620805 49
1795620810 49
1795620815 49
1795620820 49
1795620825 49
1795620830 49
1795620835 49
1795620840 49
1795620845 49
1795620850 49
1795620855 49
1795620860 50
1795620865 50
1795620870 50
1795620875 50
1795620880 50
1795620885 50
1795620890 50
1795620895 50
1795620900 52
```
</details>

---

