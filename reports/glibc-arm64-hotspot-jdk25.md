---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:49:38 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795707900 47
1795707905 47
1795707910 47
1795707915 47
1795707920 64
1795707925 64
1795707930 64
1795707935 64
1795707940 64
1795707945 64
1795707950 64
1795707955 64
1795707960 64
1795707965 64
1795707970 64
1795707975 64
1795707980 64
1795707985 64
1795707990 64
1795707995 64
```
</details>

---

