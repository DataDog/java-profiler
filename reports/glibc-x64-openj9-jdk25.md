---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 20:30:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 41-64 cores)</summary>

```
1795397189 43
1795397194 43
1795397199 43
1795397204 41
1795397209 41
1795397214 41
1795397219 41
1795397224 43
1795397229 43
1795397234 45
1795397239 45
1795397244 45
1795397249 45
1795397254 43
1795397259 43
1795397264 45
1795397269 45
1795397274 45
1795397279 64
1795397284 64
```
</details>

---

