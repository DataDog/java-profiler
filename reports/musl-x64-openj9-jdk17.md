---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 06:16:41 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 11 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (2 unique values: 51-53 cores)</summary>

```
1792145531 51
1792145536 51
1792145541 51
1792145546 51
1792145551 51
1792145556 51
1792145561 51
1792145566 51
1792145571 51
1792145576 51
1792145581 51
1792145586 51
1792145591 53
1792145596 53
1792145601 53
1792145606 53
1792145611 53
1792145616 53
1792145621 53
1792145626 53
```
</details>

---

