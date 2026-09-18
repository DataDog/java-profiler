---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:34:35 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1789716422 76
1789716427 76
1789716432 76
1789716437 76
1789716442 76
1789716447 76
1789716452 76
1789716457 76
1789716462 76
1789716467 76
1789716472 76
1789716477 76
1789716482 76
1789716487 76
1789716492 76
1789716497 76
1789716502 76
1789716507 76
1789716512 76
1789716517 96
```
</details>

---

