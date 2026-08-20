---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 12:31:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 81-89 cores)</summary>

```
1787243313 81
1787243318 81
1787243323 81
1787243328 81
1787243333 81
1787243338 81
1787243343 81
1787243348 81
1787243353 81
1787243358 81
1787243363 81
1787243369 81
1787243374 81
1787243379 81
1787243384 81
1787243389 81
1787243394 89
1787243399 89
1787243404 89
1787243409 89
```
</details>

---

