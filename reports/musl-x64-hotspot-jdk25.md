---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 13:29:12 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 56-73 cores)</summary>

```
1794939905 56
1794939910 58
1794939915 58
1794939920 58
1794939925 58
1794939930 58
1794939935 58
1794939940 67
1794939945 67
1794939950 67
1794939955 67
1794939960 67
1794939965 67
1794939970 67
1794939975 67
1794939980 67
1794939985 73
1794939990 73
1794939995 73
1794940000 73
```
</details>

---

