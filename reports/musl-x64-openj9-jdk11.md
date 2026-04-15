---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 13:31:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 956 |
| Sample Rate | 15.93/sec |
| Health Score | 996% |
| Threads | 11 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 72-78 cores)</summary>

```
1776274051 78
1776274056 78
1776274061 78
1776274066 78
1776274071 78
1776274076 78
1776274081 78
1776274086 78
1776274091 78
1776274096 78
1776274101 78
1776274106 72
1776274111 72
1776274116 72
1776274121 72
1776274126 72
1776274131 72
1776274136 72
1776274141 72
1776274146 72
```
</details>

---

