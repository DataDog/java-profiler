---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:54:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (2 unique values: 85-87 cores)</summary>

```
1795610929 87
1795610934 87
1795610939 87
1795610944 87
1795610949 87
1795610954 87
1795610959 85
1795610964 85
1795610969 85
1795610974 85
1795610979 85
1795610984 85
1795610989 85
1795610994 85
1795610999 85
1795611004 85
1795611009 85
1795611014 85
1795611019 85
1795611024 85
```
</details>

---

