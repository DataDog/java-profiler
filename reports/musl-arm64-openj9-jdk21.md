---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-02 11:43:32 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1788363437 64
1788363442 64
1788363447 64
1788363452 64
1788363457 64
1788363462 64
1788363467 59
1788363472 59
1788363477 59
1788363482 59
1788363487 59
1788363492 59
1788363497 59
1788363502 59
1788363507 59
1788363512 59
1788363517 59
1788363522 59
1788363527 59
1788363532 59
```
</details>

---

