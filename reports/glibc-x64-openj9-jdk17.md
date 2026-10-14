---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 11:49:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 11 |
| Allocations | 421 |

<details>
<summary>CPU Timeline (5 unique values: 79-96 cores)</summary>

```
1791992480 79
1791992485 79
1791992490 81
1791992495 81
1791992500 81
1791992505 81
1791992510 81
1791992515 81
1791992520 83
1791992525 83
1791992530 83
1791992535 87
1791992540 87
1791992545 87
1791992550 87
1791992555 87
1791992560 87
1791992565 87
1791992570 87
1791992575 87
```
</details>

---

