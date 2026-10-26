---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 14:59:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 325 |
| Sample Rate | 5.42/sec |
| Health Score | 339% |
| Threads | 13 |
| Allocations | 178 |

<details>
<summary>CPU Timeline (3 unique values: 34-51 cores)</summary>

```
1793040977 34
1793040982 34
1793040987 34
1793040992 34
1793040997 34
1793041002 34
1793041007 34
1793041012 34
1793041017 39
1793041022 39
1793041027 39
1793041032 39
1793041037 39
1793041042 51
1793041047 51
1793041052 51
1793041057 51
1793041062 51
1793041067 51
1793041072 51
```
</details>

---

