---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:33:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 79-89 cores)</summary>

```
1794497251 89
1794497256 89
1794497261 89
1794497267 89
1794497272 89
1794497277 89
1794497282 89
1794497287 89
1794497292 89
1794497297 89
1794497302 87
1794497307 87
1794497312 87
1794497317 87
1794497322 87
1794497327 81
1794497332 81
1794497337 79
1794497342 79
1794497347 79
```
</details>

---

