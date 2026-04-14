---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-14 13:34:31 EDT

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 15.35/sec |
| Health Score | 959% |
| Threads | 11 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (5 unique values: 71-81 cores)</summary>

```
1776187822 71
1776187827 75
1776187832 75
1776187837 75
1776187842 75
1776187847 75
1776187852 75
1776187857 75
1776187862 75
1776187867 75
1776187872 75
1776187877 75
1776187882 77
1776187887 77
1776187892 77
1776187897 77
1776187902 77
1776187907 77
1776187912 77
1776187917 79
```
</details>

---

