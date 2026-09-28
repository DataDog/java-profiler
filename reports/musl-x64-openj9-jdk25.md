---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-28 09:39:45 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 442 |
| Sample Rate | 7.37/sec |
| Health Score | 461% |
| Threads | 10 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 39-50 cores)</summary>

```
1790602505 50
1790602510 50
1790602515 39
1790602520 39
1790602525 39
1790602530 39
1790602535 39
1790602540 39
1790602545 39
1790602550 39
1790602555 39
1790602560 39
1790602565 39
1790602570 39
1790602575 39
1790602580 39
1790602585 39
1790602590 39
1790602595 39
1790602600 39
```
</details>

---

