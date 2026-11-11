---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 15:02:15 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 12 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 72-80 cores)</summary>

```
1794427032 72
1794427037 72
1794427042 72
1794427047 72
1794427052 72
1794427057 72
1794427062 72
1794427068 72
1794427073 72
1794427078 72
1794427083 72
1794427088 72
1794427093 72
1794427098 72
1794427103 80
1794427108 80
1794427113 80
1794427118 80
1794427123 80
1794427128 80
```
</details>

---

