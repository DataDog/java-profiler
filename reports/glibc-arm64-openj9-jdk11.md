---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 04:39:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 12 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 40 |
| Sample Rate | 0.67/sec |
| Health Score | 42% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776846913 64
1776846918 64
1776846923 64
1776846928 64
1776846934 64
1776846939 64
1776846944 64
1776846949 64
1776846954 64
1776846959 64
1776846964 64
1776846969 64
1776846974 64
1776846979 64
1776846984 64
1776846989 64
1776846994 64
1776846999 64
1776847004 64
1776847009 64
```
</details>

---

