---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:00:14 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 14 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794354999 34
1794355004 34
1794355009 34
1794355014 34
1794355019 34
1794355024 34
1794355029 34
1794355034 34
1794355039 39
1794355044 39
1794355049 39
1794355054 39
1794355059 39
1794355064 39
1794355069 39
1794355074 39
1794355079 39
1794355084 39
1794355089 39
1794355094 39
```
</details>

---

