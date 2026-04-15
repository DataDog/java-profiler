---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 10:34:52 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 59-85 cores)</summary>

```
1776263159 63
1776263164 63
1776263169 63
1776263174 63
1776263179 68
1776263184 68
1776263189 68
1776263194 68
1776263199 68
1776263204 68
1776263209 68
1776263214 68
1776263219 68
1776263224 59
1776263229 59
1776263234 59
1776263239 59
1776263244 59
1776263249 59
1776263254 59
```
</details>

---

