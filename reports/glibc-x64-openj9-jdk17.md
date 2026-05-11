---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 10:05:27 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 11 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 68-69 cores)</summary>

```
1778507984 69
1778507989 69
1778507994 69
1778507999 69
1778508004 69
1778508009 69
1778508014 69
1778508019 69
1778508024 68
1778508029 68
1778508034 68
1778508039 68
1778508044 68
1778508049 68
1778508054 68
1778508059 68
1778508064 68
1778508069 68
1778508074 68
1778508079 68
```
</details>

---

