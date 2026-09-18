---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:32:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 10 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 32-44 cores)</summary>

```
1789716462 40
1789716467 40
1789716472 42
1789716477 42
1789716482 44
1789716487 44
1789716492 34
1789716497 34
1789716502 34
1789716507 34
1789716512 34
1789716517 34
1789716522 34
1789716527 34
1789716532 34
1789716537 34
1789716542 34
1789716547 34
1789716552 34
1789716557 32
```
</details>

---

