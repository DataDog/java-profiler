---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:18:48 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1795641197 81
1795641202 81
1795641207 81
1795641212 81
1795641217 81
1795641222 81
1795641227 81
1795641232 81
1795641237 79
1795641242 79
1795641247 79
1795641252 79
1795641257 79
1795641262 79
1795641267 79
1795641272 79
1795641277 79
1795641282 79
1795641287 79
1795641292 79
```
</details>

---

