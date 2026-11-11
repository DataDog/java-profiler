---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:24:51 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (4 unique values: 66-86 cores)</summary>

```
1794395940 78
1794395945 78
1794395950 78
1794395955 78
1794395960 78
1794395965 78
1794395970 78
1794395975 78
1794395980 84
1794395985 84
1794395990 86
1794395995 86
1794396000 86
1794396005 86
1794396010 66
1794396015 66
1794396020 66
1794396025 66
1794396030 66
1794396035 66
```
</details>

---

