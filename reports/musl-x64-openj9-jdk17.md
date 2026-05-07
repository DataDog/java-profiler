---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 05:51:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1024 |
| Sample Rate | 17.07/sec |
| Health Score | 1067% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (5 unique values: 78-85 cores)</summary>

```
1778147282 82
1778147287 82
1778147292 78
1778147297 78
1778147302 78
1778147307 78
1778147312 78
1778147317 78
1778147322 78
1778147327 80
1778147332 80
1778147337 83
1778147342 83
1778147347 83
1778147352 83
1778147357 83
1778147362 83
1778147367 83
1778147372 83
1778147377 83
```
</details>

---

