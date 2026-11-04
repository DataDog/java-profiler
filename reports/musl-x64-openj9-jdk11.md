---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 20:28:24 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (3 unique values: 56-63 cores)</summary>

```
1793755438 56
1793755443 56
1793755448 56
1793755453 56
1793755458 56
1793755463 56
1793755468 56
1793755473 56
1793755478 56
1793755483 56
1793755488 61
1793755493 61
1793755498 61
1793755503 61
1793755508 61
1793755513 61
1793755518 61
1793755523 63
1793755528 63
1793755533 63
```
</details>

---

