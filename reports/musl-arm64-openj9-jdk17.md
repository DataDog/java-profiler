---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-07 17:34:39 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 355 |
| Sample Rate | 5.92/sec |
| Health Score | 370% |
| Threads | 9 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1778189406 64
1778189411 64
1778189416 64
1778189421 64
1778189426 64
1778189431 64
1778189436 64
1778189441 64
1778189446 64
1778189451 64
1778189456 64
1778189461 64
1778189466 64
1778189471 64
1778189476 64
1778189481 64
1778189486 54
1778189491 54
1778189496 54
1778189501 54
```
</details>

---

