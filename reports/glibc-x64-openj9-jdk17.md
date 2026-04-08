---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-08 13:30:10 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1775669038 32
1775669043 32
1775669048 30
1775669053 30
1775669058 30
1775669063 30
1775669068 30
1775669073 30
1775669078 30
1775669083 30
1775669088 30
1775669093 30
1775669098 30
1775669103 30
1775669108 30
1775669113 32
1775669118 32
1775669123 32
1775669128 32
1775669133 32
```
</details>

---

