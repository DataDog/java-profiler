---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 14:48:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 650 |
| Sample Rate | 10.83/sec |
| Health Score | 677% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 41-55 cores)</summary>

```
1778093008 51
1778093013 51
1778093018 51
1778093023 55
1778093028 55
1778093033 50
1778093038 50
1778093043 50
1778093048 50
1778093053 50
1778093058 50
1778093063 50
1778093068 50
1778093073 50
1778093078 50
1778093083 46
1778093088 46
1778093093 46
1778093098 46
1778093103 46
```
</details>

---

