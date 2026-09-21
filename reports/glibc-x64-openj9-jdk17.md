---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 16:58:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1790024021 24
1790024026 24
1790024031 24
1790024036 24
1790024041 22
1790024046 22
1790024051 22
1790024056 22
1790024061 22
1790024066 22
1790024071 22
1790024076 22
1790024081 22
1790024086 22
1790024091 22
1790024096 22
1790024101 24
1790024106 24
1790024111 32
1790024116 32
```
</details>

---

