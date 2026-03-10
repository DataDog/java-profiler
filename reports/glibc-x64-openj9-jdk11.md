---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-03-10 13:36:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 791 |
| Sample Rate | 13.18/sec |
| Health Score | 824% |
| Threads | 10 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 55-82 cores)</summary>

```
1773163972 59
1773163977 59
1773163982 59
1773163987 59
1773163992 59
1773163997 59
1773164002 59
1773164007 59
1773164012 59
1773164017 59
1773164022 59
1773164027 59
1773164032 59
1773164037 59
1773164042 55
1773164047 55
1773164052 55
1773164057 65
1773164062 65
1773164067 82
```
</details>

---

