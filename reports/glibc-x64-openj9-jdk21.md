---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-16 09:19:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 607 |
| Sample Rate | 10.12/sec |
| Health Score | 632% |
| Threads | 11 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (5 unique values: 65-90 cores)</summary>

```
1794838485 66
1794838490 66
1794838495 66
1794838500 66
1794838505 66
1794838510 66
1794838515 68
1794838520 68
1794838525 65
1794838530 65
1794838535 65
1794838540 65
1794838545 65
1794838550 65
1794838555 65
1794838560 65
1794838565 65
1794838570 70
1794838575 70
1794838580 70
```
</details>

---

