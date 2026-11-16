---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 05:31:47 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 385 |
| Sample Rate | 6.42/sec |
| Health Score | 401% |
| Threads | 9 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 82-94 cores)</summary>

```
1794824780 94
1794824785 94
1794824790 94
1794824795 94
1794824800 94
1794824805 94
1794824810 94
1794824815 94
1794824820 94
1794824825 94
1794824830 94
1794824835 82
1794824840 82
1794824845 82
1794824850 82
1794824855 82
1794824860 82
1794824865 82
1794824870 82
1794824875 82
```
</details>

---

