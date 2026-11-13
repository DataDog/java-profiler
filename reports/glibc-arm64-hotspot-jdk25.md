---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 19:03:47 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 9 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 40-46 cores)</summary>

```
1794528028 46
1794528033 40
1794528038 40
1794528043 40
1794528048 40
1794528054 40
1794528059 40
1794528064 40
1794528069 40
1794528074 45
1794528079 45
1794528084 45
1794528089 45
1794528094 45
1794528099 45
1794528104 45
1794528109 45
1794528114 45
1794528119 45
1794528124 45
```
</details>

---

