---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-22 14:08:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 15 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776881033 64
1776881038 64
1776881044 64
1776881049 64
1776881054 64
1776881059 64
1776881064 64
1776881069 64
1776881074 64
1776881079 64
1776881084 59
1776881089 59
1776881094 59
1776881099 59
1776881104 59
1776881109 59
1776881114 59
1776881119 59
1776881124 59
1776881129 59
```
</details>

---

