---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-10 13:55:47 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 24-29 cores)</summary>

```
1773164989 25
1773164994 25
1773164999 25
1773165004 25
1773165009 25
1773165014 25
1773165019 25
1773165024 29
1773165029 29
1773165034 29
1773165039 29
1773165044 29
1773165049 29
1773165054 29
1773165059 29
1773165064 24
1773165069 24
1773165074 24
1773165079 24
1773165084 24
```
</details>

---

