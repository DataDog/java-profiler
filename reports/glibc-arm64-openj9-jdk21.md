---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-21 17:14:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 15 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 41-48 cores)</summary>

```
1787346413 48
1787346418 48
1787346423 48
1787346428 48
1787346433 48
1787346438 48
1787346443 48
1787346448 48
1787346453 48
1787346458 48
1787346463 48
1787346468 48
1787346473 48
1787346478 48
1787346483 48
1787346488 48
1787346493 48
1787346498 48
1787346503 43
1787346508 43
```
</details>

---

