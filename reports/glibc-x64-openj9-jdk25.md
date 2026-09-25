---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-25 07:37:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 361 |
| Sample Rate | 6.02/sec |
| Health Score | 376% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 51-68 cores)</summary>

```
1790336007 51
1790336012 51
1790336017 51
1790336022 51
1790336027 68
1790336032 68
1790336037 68
1790336042 68
1790336047 68
1790336052 68
1790336057 68
1790336062 68
1790336067 68
1790336072 68
1790336077 68
1790336082 68
1790336087 68
1790336092 68
1790336097 68
1790336102 68
```
</details>

---

