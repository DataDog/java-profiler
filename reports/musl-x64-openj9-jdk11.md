---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-17 12:00:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 762 |
| Sample Rate | 12.70/sec |
| Health Score | 794% |
| Threads | 9 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 975 |
| Sample Rate | 16.25/sec |
| Health Score | 1016% |
| Threads | 9 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 78-84 cores)</summary>

```
1776441370 78
1776441375 80
1776441380 80
1776441385 84
1776441390 84
1776441395 84
1776441400 80
1776441405 80
1776441410 80
1776441415 80
1776441420 80
1776441425 80
1776441430 80
1776441435 80
1776441440 80
1776441445 80
1776441450 80
1776441455 80
1776441460 80
1776441465 80
```
</details>

---

