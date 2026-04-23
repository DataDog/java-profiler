---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 03:58:18 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 463 |
| Sample Rate | 7.72/sec |
| Health Score | 482% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (5 unique values: 28-36 cores)</summary>

```
1776930832 31
1776930837 31
1776930842 31
1776930847 31
1776930852 31
1776930857 31
1776930862 31
1776930867 31
1776930872 31
1776930877 36
1776930882 36
1776930887 28
1776930892 28
1776930897 33
1776930902 33
1776930907 33
1776930912 33
1776930917 33
1776930922 33
1776930927 33
```
</details>

---

