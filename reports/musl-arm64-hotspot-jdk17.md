---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:22:47 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 11 |
| Allocations | 119 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795007921 64
1795007926 64
1795007931 64
1795007936 64
1795007941 64
1795007946 64
1795007951 64
1795007956 64
1795007961 64
1795007966 64
1795007971 64
1795007976 64
1795007981 64
1795007986 64
1795007991 64
1795007996 64
1795008001 64
1795008006 64
1795008011 64
1795008016 64
```
</details>

---

