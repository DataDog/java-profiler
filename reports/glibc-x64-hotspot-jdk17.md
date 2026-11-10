---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 12:21:46 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 11 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (5 unique values: 72-92 cores)</summary>

```
1794331002 87
1794331007 87
1794331012 85
1794331017 85
1794331022 90
1794331027 90
1794331032 90
1794331037 90
1794331042 90
1794331047 92
1794331052 92
1794331057 92
1794331062 92
1794331067 92
1794331072 92
1794331077 92
1794331082 92
1794331087 92
1794331092 92
1794331097 92
```
</details>

---

