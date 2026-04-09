---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-09 05:04:59 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (4 unique values: 76-81 cores)</summary>

```
1775724969 76
1775724974 76
1775724979 81
1775724984 81
1775724989 81
1775724994 79
1775724999 79
1775725004 79
1775725009 79
1775725014 79
1775725019 79
1775725024 76
1775725029 76
1775725034 76
1775725039 76
1775725044 76
1775725049 76
1775725054 76
1775725059 78
1775725064 78
```
</details>

---

