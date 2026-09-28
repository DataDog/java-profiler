---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 09:39:45 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 944 |
| Sample Rate | 15.73/sec |
| Health Score | 983% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 49-71 cores)</summary>

```
1790602494 51
1790602499 51
1790602504 51
1790602509 51
1790602514 51
1790602519 51
1790602524 51
1790602530 51
1790602535 51
1790602540 51
1790602545 51
1790602550 51
1790602555 51
1790602560 51
1790602565 51
1790602570 49
1790602575 49
1790602580 49
1790602585 49
1790602590 49
```
</details>

---

