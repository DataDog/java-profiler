---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 09:24:32 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 870 |
| Sample Rate | 14.50/sec |
| Health Score | 906% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795702845 47
1795702850 47
1795702855 47
1795702860 47
1795702865 47
1795702870 47
1795702875 47
1795702880 47
1795702885 47
1795702890 47
1795702895 47
1795702900 47
1795702905 47
1795702910 47
1795702915 47
1795702920 47
1795702925 47
1795702930 47
1795702935 47
1795702940 47
```
</details>

---

