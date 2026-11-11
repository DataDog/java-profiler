---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 15:42:12 EST

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (5 unique values: 65-91 cores)</summary>

```
1794429423 73
1794429428 80
1794429433 80
1794429438 80
1794429443 80
1794429448 80
1794429453 80
1794429458 80
1794429463 80
1794429468 82
1794429473 82
1794429478 82
1794429483 82
1794429488 65
1794429493 65
1794429498 65
1794429503 65
1794429508 65
1794429513 65
1794429518 65
```
</details>

---

