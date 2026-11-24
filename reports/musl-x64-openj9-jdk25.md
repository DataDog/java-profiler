---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 00:03:33 EST

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (4 unique values: 25-53 cores)</summary>

```
1795496343 53
1795496348 53
1795496353 53
1795496358 53
1795496363 53
1795496368 53
1795496373 36
1795496378 36
1795496383 27
1795496388 27
1795496393 27
1795496398 27
1795496403 25
1795496408 25
1795496413 25
1795496418 25
1795496423 25
1795496428 25
1795496433 25
1795496438 25
```
</details>

---

