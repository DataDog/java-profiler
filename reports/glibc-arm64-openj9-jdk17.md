---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:43:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1789979923 48
1789979928 48
1789979933 48
1789979938 48
1789979944 48
1789979949 48
1789979954 48
1789979959 48
1789979964 48
1789979969 48
1789979974 48
1789979979 48
1789979984 48
1789979989 48
1789979994 48
1789979999 48
1789980004 48
1789980009 48
1789980014 48
1789980019 48
```
</details>

---

