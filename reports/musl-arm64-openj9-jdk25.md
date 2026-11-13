---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 08:55:22 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 10 |
| Allocations | 112 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (4 unique values: 37-40 cores)</summary>

```
1794577817 40
1794577822 40
1794577827 38
1794577832 38
1794577837 38
1794577842 38
1794577847 38
1794577852 38
1794577857 38
1794577862 38
1794577867 37
1794577872 37
1794577877 37
1794577882 37
1794577887 37
1794577892 37
1794577897 39
1794577902 39
1794577907 39
1794577912 39
```
</details>

---

