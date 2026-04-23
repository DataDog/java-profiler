---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-23 04:32:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
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
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776932921 64
1776932926 64
1776932931 64
1776932936 64
1776932941 64
1776932946 64
1776932951 64
1776932956 64
1776932961 64
1776932966 64
1776932971 64
1776932976 64
1776932981 64
1776932986 64
1776932991 64
1776932996 64
1776933001 64
1776933006 64
1776933011 64
1776933016 64
```
</details>

---

