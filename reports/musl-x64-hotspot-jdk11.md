---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-14 21:04:22 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1043 |
| Sample Rate | 17.38/sec |
| Health Score | 1086% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 32-49 cores)</summary>

```
1794707937 32
1794707942 32
1794707947 32
1794707952 32
1794707957 32
1794707962 32
1794707967 32
1794707972 32
1794707977 32
1794707982 32
1794707987 32
1794707992 32
1794707997 32
1794708002 32
1794708007 32
1794708012 32
1794708017 32
1794708022 32
1794708027 32
1794708032 32
```
</details>

---

