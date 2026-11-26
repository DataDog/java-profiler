---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 09:26:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 14 |
| Allocations | 137 |

<details>
<summary>CPU Timeline (3 unique values: 42-64 cores)</summary>

```
1795702939 42
1795702944 42
1795702949 42
1795702954 42
1795702959 42
1795702964 42
1795702969 42
1795702974 42
1795702979 42
1795702984 42
1795702989 47
1795702994 47
1795702999 47
1795703004 47
1795703009 47
1795703014 47
1795703019 47
1795703024 47
1795703029 47
1795703034 47
```
</details>

---

