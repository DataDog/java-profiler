---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-20 04:41:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (5 unique values: 56-79 cores)</summary>

```
1776674119 56
1776674124 56
1776674129 56
1776674134 56
1776674139 56
1776674144 56
1776674149 79
1776674154 79
1776674159 79
1776674164 79
1776674169 60
1776674174 60
1776674179 60
1776674184 60
1776674189 60
1776674194 58
1776674199 58
1776674204 58
1776674209 58
1776674214 58
```
</details>

---

