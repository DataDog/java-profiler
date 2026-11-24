---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 06:37:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 701 |
| Sample Rate | 11.68/sec |
| Health Score | 730% |
| Threads | 10 |
| Allocations | 482 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795519964 64
1795519969 64
1795519974 64
1795519979 64
1795519984 64
1795519989 64
1795519994 64
1795519999 64
1795520004 64
1795520009 64
1795520014 64
1795520019 64
1795520024 64
1795520029 64
1795520034 64
1795520039 64
1795520044 64
1795520049 64
1795520054 64
1795520059 64
```
</details>

---

