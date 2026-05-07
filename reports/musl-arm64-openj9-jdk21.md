---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 10:54:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1778165428 59
1778165433 59
1778165438 59
1778165443 59
1778165448 59
1778165453 54
1778165458 54
1778165463 49
1778165468 49
1778165473 49
1778165478 49
1778165483 49
1778165488 49
1778165493 49
1778165498 49
1778165503 49
1778165508 49
1778165513 49
1778165518 49
1778165523 49
```
</details>

---

