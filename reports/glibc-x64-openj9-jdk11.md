---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 07:16:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 12.63/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 90-96 cores)</summary>

```
1786446781 96
1786446786 96
1786446791 94
1786446796 94
1786446801 94
1786446806 94
1786446811 94
1786446816 92
1786446821 92
1786446826 90
1786446831 90
1786446836 90
1786446841 92
1786446846 92
1786446851 92
1786446856 92
1786446861 92
1786446866 94
1786446871 94
1786446876 94
```
</details>

---

