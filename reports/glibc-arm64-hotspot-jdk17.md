---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:25:49 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794583252 48
1794583257 48
1794583262 48
1794583267 48
1794583272 48
1794583277 48
1794583282 48
1794583287 48
1794583292 48
1794583297 48
1794583302 43
1794583307 43
1794583312 43
1794583317 43
1794583322 43
1794583327 43
1794583332 43
1794583337 43
1794583342 48
1794583347 48
```
</details>

---

