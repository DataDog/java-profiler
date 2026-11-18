---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:30:42 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 848 |
| Sample Rate | 14.13/sec |
| Health Score | 883% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (2 unique values: 62-68 cores)</summary>

```
1795011952 68
1795011957 68
1795011962 68
1795011967 68
1795011972 68
1795011977 68
1795011982 68
1795011987 68
1795011992 68
1795011997 68
1795012002 68
1795012007 68
1795012012 68
1795012017 62
1795012022 62
1795012027 62
1795012032 62
1795012037 62
1795012042 62
1795012047 62
```
</details>

---

