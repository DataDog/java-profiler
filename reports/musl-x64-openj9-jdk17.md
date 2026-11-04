---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 12:28:14 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 60-75 cores)</summary>

```
1793812774 75
1793812779 75
1793812784 75
1793812789 75
1793812794 73
1793812799 73
1793812804 73
1793812809 73
1793812814 73
1793812819 73
1793812824 73
1793812829 73
1793812834 73
1793812839 73
1793812844 73
1793812849 73
1793812854 73
1793812859 73
1793812864 73
1793812869 62
```
</details>

---

