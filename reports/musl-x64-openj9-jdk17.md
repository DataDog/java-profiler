---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-19 18:13:03 EST

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (5 unique values: 21-50 cores)</summary>

```
1795129648 21
1795129653 21
1795129658 44
1795129663 44
1795129668 23
1795129673 23
1795129678 21
1795129683 21
1795129688 21
1795129693 21
1795129698 21
1795129703 21
1795129708 21
1795129713 21
1795129718 21
1795129723 21
1795129728 21
1795129733 21
1795129738 29
1795129743 29
```
</details>

---

