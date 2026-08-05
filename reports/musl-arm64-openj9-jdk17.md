---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-05 08:26:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 10-30 cores)</summary>

```
1785932445 30
1785932450 30
1785932455 30
1785932460 30
1785932465 30
1785932470 30
1785932475 30
1785932480 30
1785932485 30
1785932490 30
1785932495 30
1785932500 10
1785932505 10
1785932510 10
1785932515 10
1785932520 10
1785932525 10
1785932530 10
1785932535 10
1785932540 10
```
</details>

---

