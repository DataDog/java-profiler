---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 12:39:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 10 |
| Allocations | 439 |

<details>
<summary>CPU Timeline (3 unique values: 23-28 cores)</summary>

```
1776962002 28
1776962007 28
1776962012 28
1776962017 28
1776962022 28
1776962027 28
1776962032 28
1776962037 28
1776962042 28
1776962047 26
1776962052 26
1776962057 26
1776962062 26
1776962067 26
1776962072 28
1776962077 28
1776962082 28
1776962087 28
1776962092 28
1776962097 28
```
</details>

---

