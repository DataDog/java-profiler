---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:45:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 38 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 12 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795642901 64
1795642906 64
1795642911 64
1795642916 54
1795642921 54
1795642926 54
1795642931 54
1795642936 54
1795642941 54
1795642946 54
1795642951 54
1795642956 54
1795642961 54
1795642966 54
1795642971 54
1795642976 54
1795642981 59
1795642986 59
1795642991 54
1795642996 54
```
</details>

---

