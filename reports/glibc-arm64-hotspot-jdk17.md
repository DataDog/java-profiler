---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 08:03:28 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 41-46 cores)</summary>

```
1794488363 46
1794488368 46
1794488373 46
1794488378 46
1794488383 46
1794488388 42
1794488393 42
1794488398 42
1794488403 42
1794488408 42
1794488413 42
1794488418 42
1794488423 42
1794488428 42
1794488433 42
1794488438 41
1794488443 41
1794488448 41
1794488453 41
1794488458 41
```
</details>

---

