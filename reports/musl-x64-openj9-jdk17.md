---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-02 05:49:14 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1788342294 96
1788342299 96
1788342304 96
1788342309 96
1788342314 96
1788342319 96
1788342324 80
1788342329 80
1788342334 80
1788342339 80
1788342344 80
1788342349 80
1788342354 80
1788342359 80
1788342364 80
1788342369 80
1788342374 78
1788342379 78
1788342384 78
1788342389 78
```
</details>

---

