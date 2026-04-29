---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 06:49:04 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 535 |
| Sample Rate | 8.92/sec |
| Health Score | 557% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 10 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (5 unique values: 34-46 cores)</summary>

```
1777459430 39
1777459435 44
1777459440 44
1777459445 44
1777459450 44
1777459455 44
1777459460 44
1777459465 44
1777459470 44
1777459475 46
1777459480 46
1777459485 46
1777459490 46
1777459495 46
1777459500 46
1777459505 46
1777459510 41
1777459515 41
1777459520 39
1777459525 39
```
</details>

---

