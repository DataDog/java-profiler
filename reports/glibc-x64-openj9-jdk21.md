---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 13:24:02 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (3 unique values: 82-86 cores)</summary>

```
1791912029 86
1791912034 86
1791912039 86
1791912044 84
1791912049 84
1791912054 84
1791912059 82
1791912064 82
1791912069 82
1791912074 82
1791912079 82
1791912084 82
1791912089 82
1791912094 84
1791912099 84
1791912104 84
1791912109 84
1791912114 84
1791912119 84
1791912124 82
```
</details>

---

