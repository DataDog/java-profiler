---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 12:33:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (4 unique values: 70-79 cores)</summary>

```
1795022918 70
1795022923 70
1795022928 70
1795022933 72
1795022938 72
1795022943 72
1795022948 72
1795022953 72
1795022958 72
1795022963 72
1795022968 72
1795022973 72
1795022978 72
1795022983 72
1795022988 72
1795022993 72
1795022998 72
1795023004 72
1795023009 77
1795023014 77
```
</details>

---

