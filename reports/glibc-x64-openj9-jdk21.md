---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 12:33:39 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 67-72 cores)</summary>

```
1795022939 67
1795022944 67
1795022949 67
1795022954 67
1795022959 67
1795022964 67
1795022969 67
1795022974 67
1795022979 67
1795022984 67
1795022989 67
1795022994 67
1795022999 67
1795023004 67
1795023009 67
1795023014 67
1795023019 72
1795023024 72
1795023029 72
1795023034 72
```
</details>

---

