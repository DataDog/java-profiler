---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-22 12:02:57 EDT

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 793 |
| Sample Rate | 13.22/sec |
| Health Score | 826% |
| Threads | 11 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (2 unique values: 33-40 cores)</summary>

```
1776873423 33
1776873428 33
1776873433 33
1776873438 33
1776873443 33
1776873448 33
1776873453 33
1776873458 33
1776873463 33
1776873468 33
1776873473 33
1776873478 33
1776873483 33
1776873488 33
1776873493 33
1776873498 33
1776873503 40
1776873508 40
1776873513 40
1776873518 40
```
</details>

---

