---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 12:41:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1019 |
| Sample Rate | 16.98/sec |
| Health Score | 1061% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (6 unique values: 73-81 cores)</summary>

```
1778171839 73
1778171844 73
1778171849 73
1778171854 73
1778171859 73
1778171864 78
1778171869 78
1778171874 78
1778171879 78
1778171884 78
1778171889 80
1778171894 80
1778171899 76
1778171904 76
1778171909 76
1778171914 76
1778171919 79
1778171924 79
1778171929 81
1778171934 81
```
</details>

---

