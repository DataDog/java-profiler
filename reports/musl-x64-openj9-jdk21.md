---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 12:41:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (4 unique values: 51-70 cores)</summary>

```
1778171839 54
1778171844 54
1778171849 54
1778171854 54
1778171859 54
1778171864 51
1778171869 51
1778171874 51
1778171879 51
1778171884 51
1778171889 51
1778171894 51
1778171899 51
1778171904 51
1778171909 51
1778171914 51
1778171919 66
1778171924 66
1778171929 66
1778171934 66
```
</details>

---

