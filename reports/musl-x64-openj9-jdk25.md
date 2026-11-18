---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 03:00:23 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 21-41 cores)</summary>

```
1794988434 24
1794988439 24
1794988444 24
1794988449 24
1794988454 24
1794988459 24
1794988464 24
1794988469 24
1794988474 24
1794988480 21
1794988485 21
1794988490 21
1794988495 21
1794988500 41
1794988505 41
1794988510 41
1794988515 41
1794988520 41
1794988525 41
1794988530 41
```
</details>

---

