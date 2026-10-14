---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-14 12:40:14 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 885 |
| Sample Rate | 14.75/sec |
| Health Score | 922% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1791995647 84
1791995652 84
1791995657 84
1791995662 84
1791995667 84
1791995672 84
1791995677 84
1791995682 84
1791995687 84
1791995692 84
1791995697 84
1791995702 82
1791995707 82
1791995712 82
1791995717 82
1791995722 86
1791995727 86
1791995732 86
1791995737 86
1791995742 86
```
</details>

---

