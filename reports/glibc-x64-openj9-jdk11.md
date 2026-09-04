---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (2 unique values: 88-92 cores)</summary>

```
1788530924 92
1788530929 92
1788530934 88
1788530939 88
1788530944 88
1788530949 88
1788530954 88
1788530959 88
1788530964 88
1788530969 88
1788530974 88
1788530979 88
1788530984 88
1788530989 88
1788530994 88
1788530999 88
1788531004 88
1788531009 88
1788531014 88
1788531019 88
```
</details>

---

