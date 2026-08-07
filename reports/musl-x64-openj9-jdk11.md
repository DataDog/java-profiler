---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-06 22:26:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 724 |
| Sample Rate | 12.07/sec |
| Health Score | 754% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (3 unique values: 74-76 cores)</summary>

```
1786069295 74
1786069300 76
1786069306 76
1786069311 76
1786069316 76
1786069321 76
1786069326 76
1786069331 76
1786069336 76
1786069341 76
1786069346 76
1786069351 76
1786069356 76
1786069361 76
1786069366 76
1786069371 76
1786069376 75
1786069381 75
1786069386 75
1786069391 75
```
</details>

---

