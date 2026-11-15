---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 18:26:28 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 409 |
| Sample Rate | 6.82/sec |
| Health Score | 426% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 86-94 cores)</summary>

```
1794785003 86
1794785008 86
1794785013 86
1794785018 86
1794785023 86
1794785028 86
1794785033 86
1794785038 86
1794785043 86
1794785048 86
1794785053 86
1794785058 86
1794785063 86
1794785068 94
1794785073 94
1794785078 94
1794785083 94
1794785089 94
1794785094 94
1794785099 94
```
</details>

---

