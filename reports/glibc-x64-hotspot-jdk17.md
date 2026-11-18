---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:20:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (3 unique values: 66-70 cores)</summary>

```
1795014939 68
1795014944 68
1795014949 68
1795014954 68
1795014959 68
1795014964 70
1795014969 70
1795014974 70
1795014979 70
1795014984 70
1795014989 70
1795014994 66
1795014999 66
1795015004 66
1795015009 66
1795015014 66
1795015019 66
1795015024 66
1795015029 66
1795015034 66
```
</details>

---

