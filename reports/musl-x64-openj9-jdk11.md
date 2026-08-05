---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-05 08:26:03 EDT

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
| CPU Cores (start) | 93 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 87-93 cores)</summary>

```
1785932425 93
1785932430 93
1785932435 93
1785932440 93
1785932445 89
1785932450 89
1785932455 89
1785932460 89
1785932465 89
1785932470 89
1785932475 89
1785932480 89
1785932485 89
1785932490 89
1785932495 89
1785932500 89
1785932505 89
1785932510 87
1785932515 87
1785932520 87
```
</details>

---

