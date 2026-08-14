---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-14 05:49:18 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 9 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (5 unique values: 45-52 cores)</summary>

```
1786700608 52
1786700613 52
1786700618 52
1786700623 52
1786700628 52
1786700633 52
1786700638 52
1786700643 52
1786700648 52
1786700653 52
1786700658 51
1786700663 51
1786700668 51
1786700673 46
1786700678 46
1786700683 45
1786700688 45
1786700693 45
1786700698 45
1786700703 45
```
</details>

---

