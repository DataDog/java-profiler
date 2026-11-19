---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:28:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 609 |
| Sample Rate | 10.15/sec |
| Health Score | 634% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (4 unique values: 62-79 cores)</summary>

```
1795112527 62
1795112532 62
1795112537 62
1795112542 62
1795112547 62
1795112552 62
1795112557 62
1795112562 62
1795112567 62
1795112572 62
1795112577 62
1795112582 71
1795112587 71
1795112592 71
1795112597 71
1795112602 79
1795112607 79
1795112612 79
1795112617 75
1795112622 75
```
</details>

---

