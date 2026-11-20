---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:12:26 EST

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1795194413 87
1795194418 87
1795194423 87
1795194428 87
1795194433 87
1795194438 87
1795194443 87
1795194448 87
1795194453 87
1795194458 87
1795194463 87
1795194468 87
1795194473 87
1795194478 87
1795194483 85
1795194488 85
1795194493 85
1795194498 85
1795194503 85
1795194508 85
```
</details>

---

