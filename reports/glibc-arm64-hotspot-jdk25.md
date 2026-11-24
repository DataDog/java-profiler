---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 06:19:48 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 9 |
| Allocations | 126 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 28-59 cores)</summary>

```
1795518967 33
1795518972 33
1795518977 33
1795518982 33
1795518987 33
1795518992 33
1795518997 33
1795519002 33
1795519007 33
1795519012 33
1795519017 28
1795519022 28
1795519027 28
1795519032 28
1795519037 28
1795519042 28
1795519047 28
1795519052 28
1795519057 59
1795519062 59
```
</details>

---

