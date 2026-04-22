---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-22 12:02:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 76-86 cores)</summary>

```
1776873403 81
1776873408 81
1776873413 81
1776873418 81
1776873423 81
1776873428 81
1776873433 81
1776873438 81
1776873443 81
1776873448 81
1776873453 81
1776873458 81
1776873463 81
1776873468 81
1776873473 86
1776873478 86
1776873483 86
1776873488 86
1776873493 86
1776873498 86
```
</details>

---

