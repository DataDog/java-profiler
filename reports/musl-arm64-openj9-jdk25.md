---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-07 10:30:57 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 7 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 19-32 cores)</summary>

```
1786112817 32
1786112822 32
1786112827 32
1786112832 32
1786112837 32
1786112842 32
1786112847 32
1786112852 32
1786112857 32
1786112862 32
1786112867 32
1786112872 32
1786112877 32
1786112882 32
1786112887 32
1786112892 32
1786112897 19
1786112902 19
1786112907 19
1786112912 19
```
</details>

---

