---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 07:10:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 924 |
| Sample Rate | 15.40/sec |
| Health Score | 962% |
| Threads | 10 |
| Allocations | 572 |

<details>
<summary>CPU Timeline (2 unique values: 45-47 cores)</summary>

```
1793880374 45
1793880379 45
1793880384 45
1793880389 45
1793880394 45
1793880399 45
1793880404 45
1793880409 45
1793880414 45
1793880419 45
1793880424 45
1793880429 45
1793880434 47
1793880439 47
1793880444 47
1793880449 47
1793880455 47
1793880460 47
1793880465 47
1793880470 47
```
</details>

---

