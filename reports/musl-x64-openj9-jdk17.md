---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-13 13:24:03 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 22-30 cores)</summary>

```
1791911829 30
1791911834 30
1791911839 30
1791911844 30
1791911849 30
1791911854 30
1791911859 30
1791911864 30
1791911869 30
1791911874 30
1791911879 30
1791911884 30
1791911889 30
1791911894 22
1791911899 22
1791911904 22
1791911909 22
1791911914 22
1791911919 22
1791911924 24
```
</details>

---

