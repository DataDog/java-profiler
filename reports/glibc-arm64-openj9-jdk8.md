---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-10 11:38:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 36-44 cores)</summary>

```
1786376027 36
1786376032 36
1786376037 36
1786376042 36
1786376047 44
1786376052 44
1786376057 44
1786376062 44
1786376067 44
1786376072 44
1786376077 44
1786376082 44
1786376087 44
1786376092 44
1786376097 44
1786376102 44
1786376107 44
1786376112 44
1786376117 44
1786376122 44
```
</details>

---

