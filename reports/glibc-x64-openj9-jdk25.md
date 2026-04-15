---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 13:31:16 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 10 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (5 unique values: 69-79 cores)</summary>

```
1776274056 77
1776274061 77
1776274066 77
1776274071 77
1776274076 77
1776274081 77
1776274086 77
1776274091 73
1776274096 73
1776274101 73
1776274106 73
1776274111 73
1776274116 73
1776274121 73
1776274126 75
1776274131 75
1776274136 75
1776274141 79
1776274146 79
1776274151 75
```
</details>

---

