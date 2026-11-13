---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:15:29 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 61-78 cores)</summary>

```
1794582650 70
1794582655 70
1794582660 61
1794582665 61
1794582670 61
1794582675 61
1794582680 61
1794582685 61
1794582690 78
1794582695 78
1794582700 78
1794582705 78
1794582710 78
1794582715 78
1794582720 78
1794582725 78
1794582730 78
1794582735 78
1794582740 78
1794582745 78
```
</details>

---

