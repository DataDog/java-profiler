---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 16:04:56 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 9 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 23-29 cores)</summary>

```
1794430832 29
1794430837 29
1794430842 29
1794430847 29
1794430852 29
1794430857 29
1794430862 23
1794430867 23
1794430872 23
1794430877 23
1794430882 23
1794430887 23
1794430892 23
1794430897 23
1794430902 23
1794430907 23
1794430912 23
1794430917 23
1794430922 23
1794430927 23
```
</details>

---

