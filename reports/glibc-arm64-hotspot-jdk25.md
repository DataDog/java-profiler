---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 08:48:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 6 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (4 unique values: 31-34 cores)</summary>

```
1795095830 31
1795095835 34
1795095840 34
1795095845 33
1795095850 33
1795095855 33
1795095860 33
1795095865 34
1795095870 34
1795095875 34
1795095880 34
1795095885 34
1795095890 34
1795095895 34
1795095900 34
1795095905 34
1795095910 34
1795095915 34
1795095920 34
1795095925 32
```
</details>

---

