---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 10:34:51 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 9 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 55-60 cores)</summary>

```
1776263189 55
1776263194 55
1776263199 55
1776263204 55
1776263209 55
1776263214 55
1776263219 55
1776263224 55
1776263229 60
1776263234 60
1776263239 60
1776263244 60
1776263249 60
1776263254 60
1776263259 60
1776263264 60
1776263269 56
1776263274 56
1776263279 56
1776263284 56
```
</details>

---

