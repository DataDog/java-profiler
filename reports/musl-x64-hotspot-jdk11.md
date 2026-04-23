---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-23 12:53:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 49-59 cores)</summary>

```
1776962890 49
1776962895 49
1776962900 49
1776962905 49
1776962910 49
1776962915 59
1776962920 59
1776962925 59
1776962930 59
1776962935 59
1776962940 59
1776962945 59
1776962950 59
1776962955 59
1776962960 59
1776962965 59
1776962970 59
1776962975 59
1776962980 59
1776962985 59
```
</details>

---

