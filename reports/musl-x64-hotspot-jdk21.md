---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 12:07:22 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (8 unique values: 72-89 cores)</summary>

```
1794934929 82
1794934934 85
1794934939 85
1794934944 85
1794934949 85
1794934954 87
1794934959 87
1794934964 87
1794934969 89
1794934974 89
1794934979 89
1794934984 89
1794934989 72
1794934994 72
1794934999 72
1794935004 77
1794935009 77
1794935014 75
1794935019 75
1794935024 75
```
</details>

---

