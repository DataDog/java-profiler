---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 10:37:15 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 158 |
| Sample Rate | 2.63/sec |
| Health Score | 164% |
| Threads | 8 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1786977232 44
1786977238 44
1786977243 44
1786977248 44
1786977253 48
1786977258 48
1786977263 48
1786977268 48
1786977273 43
1786977278 43
1786977283 43
1786977288 43
1786977293 43
1786977298 43
1786977303 43
1786977308 43
1786977313 43
1786977318 43
1786977323 43
1786977328 43
```
</details>

---

