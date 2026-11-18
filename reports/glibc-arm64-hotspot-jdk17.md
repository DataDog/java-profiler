---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:22:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 14 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 36-38 cores)</summary>

```
1795007941 36
1795007946 36
1795007951 36
1795007956 36
1795007961 36
1795007966 38
1795007971 38
1795007976 38
1795007981 38
1795007986 38
1795007991 38
1795007996 38
1795008001 38
1795008006 38
1795008011 38
1795008017 38
1795008022 38
1795008027 38
1795008032 38
1795008037 38
```
</details>

---

