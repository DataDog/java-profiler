---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 06:36:23 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 21-46 cores)</summary>

```
1794396730 46
1794396735 46
1794396740 46
1794396745 46
1794396750 46
1794396755 46
1794396760 46
1794396765 46
1794396771 46
1794396776 46
1794396781 21
1794396786 21
1794396791 21
1794396796 21
1794396801 21
1794396806 21
1794396811 21
1794396816 21
1794396821 21
1794396826 21
```
</details>

---

