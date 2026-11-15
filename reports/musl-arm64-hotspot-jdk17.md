---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-14 21:04:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794707962 48
1794707967 48
1794707972 48
1794707977 48
1794707982 48
1794707987 48
1794707992 48
1794707997 48
1794708002 48
1794708007 48
1794708012 48
1794708017 48
1794708022 48
1794708027 48
1794708032 43
1794708037 43
1794708042 43
1794708047 43
1794708052 43
1794708057 43
```
</details>

---

