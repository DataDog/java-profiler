---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 20:31:39 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795397227 34
1795397232 34
1795397237 34
1795397242 34
1795397247 34
1795397252 34
1795397257 34
1795397262 34
1795397267 34
1795397272 34
1795397277 34
1795397282 34
1795397287 29
1795397292 29
1795397297 29
1795397302 29
1795397307 29
1795397312 29
1795397317 29
1795397322 29
```
</details>

---

