---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 04:29:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 68-87 cores)</summary>

```
1776673404 69
1776673409 68
1776673414 68
1776673419 68
1776673424 68
1776673429 68
1776673434 68
1776673439 68
1776673444 87
1776673449 87
1776673454 87
1776673459 87
1776673464 87
1776673469 87
1776673474 87
1776673479 87
1776673485 70
1776673490 70
1776673495 70
1776673500 70
```
</details>

---

