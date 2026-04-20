---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 04:29:00 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1070 |
| Sample Rate | 17.83/sec |
| Health Score | 1114% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (4 unique values: 65-74 cores)</summary>

```
1776673420 69
1776673425 69
1776673430 69
1776673435 69
1776673440 69
1776673445 69
1776673450 69
1776673455 69
1776673460 69
1776673465 69
1776673470 69
1776673475 69
1776673480 69
1776673485 69
1776673490 65
1776673495 65
1776673501 65
1776673506 65
1776673511 70
1776673516 70
```
</details>

---

