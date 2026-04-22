---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 13:04:06 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 746 |
| Sample Rate | 12.43/sec |
| Health Score | 777% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 76-87 cores)</summary>

```
1776876844 76
1776876849 76
1776876854 76
1776876859 76
1776876864 85
1776876869 85
1776876874 85
1776876879 85
1776876884 85
1776876889 85
1776876894 85
1776876899 85
1776876904 85
1776876909 85
1776876914 87
1776876919 87
1776876924 82
1776876929 82
1776876934 82
1776876939 87
```
</details>

---

