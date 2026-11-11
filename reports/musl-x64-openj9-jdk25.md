---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:42:12 EST

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (5 unique values: 66-88 cores)</summary>

```
1794429423 66
1794429428 86
1794429433 86
1794429438 86
1794429443 86
1794429448 86
1794429453 86
1794429458 86
1794429463 86
1794429468 86
1794429473 86
1794429478 86
1794429483 86
1794429488 86
1794429493 88
1794429498 88
1794429503 85
1794429509 85
1794429514 85
1794429519 85
```
</details>

---

