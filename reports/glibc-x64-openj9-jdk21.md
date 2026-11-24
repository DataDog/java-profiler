---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-24 06:37:32 EST

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 783 |
| Sample Rate | 13.05/sec |
| Health Score | 816% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 58-81 cores)</summary>

```
1795519978 77
1795519983 77
1795519988 77
1795519993 77
1795519998 77
1795520003 79
1795520008 79
1795520013 81
1795520018 81
1795520023 81
1795520028 81
1795520033 58
1795520038 58
1795520043 58
1795520048 58
1795520053 58
1795520058 58
1795520063 58
1795520068 58
1795520073 58
```
</details>

---

