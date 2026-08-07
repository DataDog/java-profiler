---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-07 10:30:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1786112852 46
1786112857 46
1786112862 46
1786112867 46
1786112872 46
1786112877 51
1786112882 51
1786112887 51
1786112892 51
1786112897 51
1786112902 51
1786112907 51
1786112912 51
1786112917 51
1786112922 51
1786112927 51
1786112932 51
1786112937 51
1786112942 51
1786112947 51
```
</details>

---

