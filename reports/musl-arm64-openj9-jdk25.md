---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 03:59:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1791532550 46
1791532556 46
1791532561 46
1791532566 46
1791532571 46
1791532576 46
1791532581 46
1791532586 46
1791532591 46
1791532596 46
1791532601 51
1791532606 51
1791532611 51
1791532616 51
1791532621 51
1791532626 51
1791532631 51
1791532636 51
1791532641 51
1791532646 51
```
</details>

---

