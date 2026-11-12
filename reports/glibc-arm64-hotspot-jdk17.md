---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:32:57 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 266 |
| Sample Rate | 4.43/sec |
| Health Score | 277% |
| Threads | 9 |
| Allocations | 144 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794497267 38
1794497272 38
1794497277 38
1794497282 38
1794497287 38
1794497292 38
1794497297 38
1794497302 43
1794497307 43
1794497312 43
1794497317 43
1794497322 43
1794497327 43
1794497332 43
1794497337 43
1794497342 48
1794497347 48
1794497352 48
1794497357 48
1794497362 48
```
</details>

---

