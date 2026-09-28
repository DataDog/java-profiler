---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-28 00:58:18 EDT

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
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 15 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1790571267 34
1790571272 34
1790571277 34
1790571282 34
1790571287 34
1790571292 34
1790571297 34
1790571302 34
1790571307 34
1790571312 34
1790571317 34
1790571322 34
1790571327 34
1790571332 34
1790571337 34
1790571342 34
1790571347 34
1790571352 34
1790571357 34
1790571362 34
```
</details>

---

