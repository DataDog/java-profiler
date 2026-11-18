---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 08:22:45 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 9 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 13 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795007929 46
1795007934 46
1795007939 46
1795007944 46
1795007949 46
1795007954 46
1795007959 46
1795007964 46
1795007969 46
1795007974 46
1795007979 46
1795007984 46
1795007989 46
1795007994 46
1795007999 46
1795008004 51
1795008009 51
1795008014 51
1795008019 51
1795008024 51
```
</details>

---

