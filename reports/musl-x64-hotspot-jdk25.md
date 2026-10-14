---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-14 12:30:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 418 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 12 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (2 unique values: 87-89 cores)</summary>

```
1791995052 89
1791995057 89
1791995062 89
1791995067 89
1791995072 89
1791995077 89
1791995082 89
1791995087 89
1791995092 89
1791995097 89
1791995102 89
1791995107 89
1791995112 89
1791995117 87
1791995122 87
1791995127 87
1791995132 87
1791995137 87
1791995142 87
1791995147 87
```
</details>

---

