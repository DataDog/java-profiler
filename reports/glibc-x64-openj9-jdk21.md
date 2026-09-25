---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-25 09:23:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 10 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 28-40 cores)</summary>

```
1790342299 40
1790342304 40
1790342309 38
1790342314 38
1790342319 38
1790342324 38
1790342329 38
1790342334 38
1790342339 38
1790342344 38
1790342349 40
1790342354 40
1790342359 40
1790342364 40
1790342369 40
1790342374 40
1790342379 40
1790342384 40
1790342389 40
1790342394 40
```
</details>

---

