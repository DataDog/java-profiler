---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 04:32:56 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 11 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 33-42 cores)</summary>

```
1776932908 37
1776932913 37
1776932918 37
1776932923 37
1776932928 37
1776932933 37
1776932938 35
1776932943 35
1776932948 35
1776932953 35
1776932959 33
1776932964 33
1776932969 40
1776932974 40
1776932979 42
1776932984 42
1776932989 42
1776932994 42
1776932999 42
1776933004 42
```
</details>

---

