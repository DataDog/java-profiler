---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 18:26:30 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 947 |
| Sample Rate | 15.78/sec |
| Health Score | 986% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 84-94 cores)</summary>

```
1794784977 84
1794784982 84
1794784987 86
1794784992 86
1794784997 86
1794785002 86
1794785007 86
1794785012 86
1794785017 86
1794785022 86
1794785027 86
1794785032 86
1794785037 86
1794785042 86
1794785047 86
1794785052 86
1794785057 86
1794785062 86
1794785067 94
1794785072 94
```
</details>

---

