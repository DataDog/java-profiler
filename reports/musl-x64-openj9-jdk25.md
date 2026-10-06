---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-06 08:29:13 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 54-58 cores)</summary>

```
1791289466 58
1791289471 58
1791289476 58
1791289481 58
1791289486 58
1791289491 58
1791289496 58
1791289501 58
1791289506 58
1791289511 58
1791289516 54
1791289521 54
1791289526 54
1791289531 54
1791289536 54
1791289541 54
1791289546 54
1791289551 54
1791289556 54
1791289561 54
```
</details>

---

