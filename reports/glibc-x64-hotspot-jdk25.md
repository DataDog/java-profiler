---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-29 12:19:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 19.07/sec |
| Health Score | 1192% |
| Threads | 11 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 743 |
| Sample Rate | 24.77/sec |
| Health Score | 1548% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 60-68 cores)</summary>

```
1769706804 68
1769706809 68
1769706814 68
1769706819 68
1769706824 68
1769706829 68
1769706834 65
1769706839 65
1769706844 65
1769706849 65
1769706854 65
1769706859 65
1769706864 65
1769706869 65
1769706874 60
1769706879 60
1769706884 60
1769706889 60
1769706894 60
1769706899 60
```
</details>

---

