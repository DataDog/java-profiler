---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 06:37:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1795519949 79
1795519954 79
1795519959 79
1795519964 79
1795519969 79
1795519974 79
1795519979 79
1795519984 79
1795519989 79
1795519994 79
1795519999 79
1795520004 79
1795520009 79
1795520014 79
1795520019 79
1795520024 79
1795520029 79
1795520034 79
1795520039 77
1795520044 77
```
</details>

---

