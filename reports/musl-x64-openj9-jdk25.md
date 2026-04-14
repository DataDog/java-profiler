---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-14 13:34:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
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
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 68-84 cores)</summary>

```
1776187833 68
1776187838 68
1776187843 68
1776187848 68
1776187853 68
1776187858 68
1776187863 72
1776187868 72
1776187873 72
1776187878 72
1776187883 72
1776187888 72
1776187893 72
1776187898 72
1776187903 72
1776187908 72
1776187913 76
1776187918 76
1776187923 76
1776187928 81
```
</details>

---

