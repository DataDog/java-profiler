---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:10:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 8 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 54-74 cores)</summary>

```
1793880364 54
1793880369 54
1793880374 54
1793880379 54
1793880384 74
1793880389 74
1793880394 74
1793880399 74
1793880404 74
1793880409 74
1793880414 74
1793880419 74
1793880424 74
1793880429 74
1793880434 74
1793880439 74
1793880444 74
1793880449 74
1793880454 74
1793880459 74
```
</details>

---

