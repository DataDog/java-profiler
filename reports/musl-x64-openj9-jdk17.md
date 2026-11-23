---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:59:24 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (4 unique values: 54-58 cores)</summary>

```
1795452882 58
1795452887 58
1795452892 58
1795452897 56
1795452902 56
1795452907 56
1795452912 56
1795452917 56
1795452922 56
1795452927 56
1795452932 56
1795452937 56
1795452942 56
1795452947 56
1795452952 56
1795452957 56
1795452962 56
1795452967 56
1795452972 56
1795452977 54
```
</details>

---

