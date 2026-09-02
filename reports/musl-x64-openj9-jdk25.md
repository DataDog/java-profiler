---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 05:49:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1788342274 96
1788342279 96
1788342284 96
1788342289 96
1788342294 96
1788342299 96
1788342304 96
1788342309 96
1788342314 96
1788342319 96
1788342324 96
1788342329 96
1788342334 76
1788342339 76
1788342344 76
1788342349 76
1788342354 76
1788342359 76
1788342364 76
1788342369 76
```
</details>

---

