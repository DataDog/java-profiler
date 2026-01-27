---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-27 10:22:45 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 23.83/sec |
| Health Score | 1489% |
| Threads | 10 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 873 |
| Sample Rate | 29.10/sec |
| Health Score | 1819% |
| Threads | 12 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1769526901 76
1769526906 76
1769526911 76
1769526916 76
1769526921 76
1769526926 76
1769526931 74
1769526936 74
1769526941 74
1769526946 74
1769526951 74
1769526956 74
1769526961 74
1769526966 74
1769526971 74
1769526976 74
1769526981 74
1769526986 74
1769526991 74
1769526996 74
```
</details>

---

