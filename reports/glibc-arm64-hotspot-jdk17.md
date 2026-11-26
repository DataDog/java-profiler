---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 09:26:36 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 304 |
| Sample Rate | 5.07/sec |
| Health Score | 317% |
| Threads | 13 |
| Allocations | 152 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795702944 47
1795702949 47
1795702954 42
1795702959 42
1795702964 42
1795702969 42
1795702974 42
1795702979 42
1795702984 42
1795702989 42
1795702994 42
1795702999 42
1795703004 42
1795703009 42
1795703014 42
1795703019 42
1795703024 42
1795703029 42
1795703034 47
1795703039 47
```
</details>

---

