---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 06:16:41 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 623 |
| Sample Rate | 10.38/sec |
| Health Score | 649% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 55-96 cores)</summary>

```
1792145501 96
1792145506 96
1792145511 96
1792145516 75
1792145521 75
1792145526 75
1792145531 75
1792145536 75
1792145541 75
1792145546 75
1792145551 75
1792145556 75
1792145561 75
1792145566 75
1792145571 75
1792145576 75
1792145581 75
1792145586 75
1792145591 75
1792145596 75
```
</details>

---

