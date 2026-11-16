---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:16:18 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 70-79 cores)</summary>

```
1794823669 72
1794823674 72
1794823679 72
1794823685 72
1794823690 70
1794823695 70
1794823700 70
1794823705 70
1794823710 70
1794823715 70
1794823720 70
1794823725 70
1794823730 70
1794823735 79
1794823740 79
1794823745 79
1794823750 77
1794823755 77
1794823760 77
1794823765 77
```
</details>

---

