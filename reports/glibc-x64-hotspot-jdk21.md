---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-06 08:27:25 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 725 |
| Sample Rate | 12.08/sec |
| Health Score | 755% |
| Threads | 9 |
| Allocations | 344 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 11 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (4 unique values: 62-67 cores)</summary>

```
1786018979 66
1786018984 66
1786018989 66
1786018994 66
1786018999 66
1786019004 66
1786019009 66
1786019014 66
1786019019 66
1786019024 66
1786019029 66
1786019034 66
1786019039 66
1786019044 62
1786019049 62
1786019054 62
1786019059 62
1786019064 62
1786019069 65
1786019074 65
```
</details>

---

