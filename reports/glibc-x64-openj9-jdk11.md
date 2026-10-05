---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-05 03:35:41 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 8 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1791185410 96
1791185415 96
1791185420 96
1791185425 94
1791185430 94
1791185435 94
1791185440 94
1791185445 94
1791185450 94
1791185455 94
1791185460 94
1791185465 94
1791185470 94
1791185475 94
1791185480 94
1791185485 94
1791185490 94
1791185495 94
1791185500 94
1791185505 94
```
</details>

---

