---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 09:39:45 EDT

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 76-96 cores)</summary>

```
1790602515 78
1790602520 78
1790602525 78
1790602530 78
1790602535 78
1790602540 78
1790602545 78
1790602550 78
1790602555 78
1790602560 78
1790602565 78
1790602570 78
1790602575 78
1790602580 78
1790602585 78
1790602590 76
1790602596 76
1790602601 76
1790602606 76
1790602611 94
```
</details>

---

