---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 09:26:37 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1795702950 48
1795702955 48
1795702960 48
1795702965 48
1795702970 48
1795702975 48
1795702980 48
1795702985 48
1795702990 48
1795702995 48
1795703000 48
1795703005 48
1795703010 48
1795703015 48
1795703020 48
1795703025 48
1795703030 48
1795703035 48
1795703040 47
1795703045 47
```
</details>

---

