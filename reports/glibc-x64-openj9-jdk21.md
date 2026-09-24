---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 04:39:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (5 unique values: 89-96 cores)</summary>

```
1790238918 96
1790238923 94
1790238928 94
1790238933 94
1790238938 94
1790238943 94
1790238948 94
1790238953 94
1790238958 94
1790238963 94
1790238968 94
1790238973 90
1790238978 90
1790238983 90
1790238988 90
1790238993 90
1790238998 90
1790239003 89
1790239008 89
1790239013 89
```
</details>

---

