---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-14 08:32:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 881 |
| Sample Rate | 14.68/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (4 unique values: 82-87 cores)</summary>

```
1791980567 87
1791980572 82
1791980577 82
1791980582 82
1791980587 82
1791980592 82
1791980597 82
1791980602 82
1791980607 82
1791980612 84
1791980617 84
1791980622 84
1791980627 84
1791980632 84
1791980637 84
1791980642 84
1791980647 87
1791980652 87
1791980657 87
1791980662 87
```
</details>

---

