---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 10:20:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 296 |
| Sample Rate | 4.93/sec |
| Health Score | 308% |
| Threads | 9 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795014969 33
1795014974 38
1795014979 38
1795014984 33
1795014989 33
1795014994 33
1795014999 33
1795015004 33
1795015009 33
1795015014 33
1795015019 33
1795015024 33
1795015029 33
1795015034 33
1795015039 33
1795015044 33
1795015049 33
1795015054 33
1795015059 33
1795015064 33
```
</details>

---

