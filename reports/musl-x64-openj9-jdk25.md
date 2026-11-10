---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 06:47:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 12 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 52-66 cores)</summary>

```
1794310963 66
1794310968 66
1794310973 66
1794310978 66
1794310983 66
1794310988 66
1794310993 66
1794310998 66
1794311003 61
1794311008 61
1794311013 61
1794311018 61
1794311023 61
1794311028 61
1794311033 61
1794311038 61
1794311043 61
1794311048 61
1794311053 61
1794311058 61
```
</details>

---

