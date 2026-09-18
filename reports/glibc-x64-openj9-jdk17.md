---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:38:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 310 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (3 unique values: 76-96 cores)</summary>

```
1789716427 96
1789716432 96
1789716437 96
1789716442 94
1789716447 94
1789716452 94
1789716457 94
1789716462 94
1789716467 94
1789716472 94
1789716477 94
1789716482 94
1789716487 94
1789716492 94
1789716497 94
1789716502 94
1789716507 96
1789716512 96
1789716517 76
1789716522 76
```
</details>

---

