---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:02:51 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 935 |
| Sample Rate | 15.58/sec |
| Health Score | 974% |
| Threads | 11 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (7 unique values: 36-81 cores)</summary>

```
1794927373 40
1794927378 38
1794927383 38
1794927388 38
1794927393 38
1794927398 38
1794927403 38
1794927408 38
1794927413 36
1794927418 36
1794927423 55
1794927428 55
1794927433 55
1794927438 55
1794927443 55
1794927448 55
1794927453 55
1794927458 77
1794927463 77
1794927468 79
```
</details>

---

