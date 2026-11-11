---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:04:54 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 76-88 cores)</summary>

```
1794430795 81
1794430800 81
1794430805 81
1794430810 81
1794430815 81
1794430820 81
1794430825 81
1794430830 81
1794430835 88
1794430840 88
1794430845 88
1794430850 88
1794430855 82
1794430860 82
1794430865 82
1794430871 76
1794430876 76
1794430881 76
1794430886 76
1794430891 76
```
</details>

---

