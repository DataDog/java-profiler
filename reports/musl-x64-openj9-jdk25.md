---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-26 06:37:55 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 83-91 cores)</summary>

```
1787740368 88
1787740373 88
1787740378 88
1787740383 88
1787740388 88
1787740393 88
1787740398 88
1787740403 88
1787740408 88
1787740413 88
1787740418 88
1787740423 88
1787740428 88
1787740433 88
1787740438 88
1787740443 83
1787740448 83
1787740453 83
1787740458 83
1787740463 83
```
</details>

---

