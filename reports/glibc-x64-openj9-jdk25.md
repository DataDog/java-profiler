---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 05:57:37 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (4 unique values: 86-91 cores)</summary>

```
1794826455 91
1794826460 91
1794826465 89
1794826470 89
1794826475 89
1794826480 89
1794826485 89
1794826490 89
1794826495 89
1794826500 86
1794826505 86
1794826510 86
1794826515 86
1794826520 86
1794826525 86
1794826530 86
1794826535 86
1794826540 86
1794826545 86
1794826550 86
```
</details>

---

