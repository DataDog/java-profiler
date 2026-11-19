---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:10:53 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 929 |
| Sample Rate | 15.48/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1795107999 50
1795108004 50
1795108009 50
1795108014 50
1795108019 50
1795108024 50
1795108029 50
1795108034 50
1795108039 50
1795108044 45
1795108049 45
1795108054 45
1795108059 45
1795108064 45
1795108069 45
1795108074 45
1795108079 45
1795108084 45
1795108089 45
1795108094 45
```
</details>

---

