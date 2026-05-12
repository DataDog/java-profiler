---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-12 06:42:14 EDT

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 941 |
| Sample Rate | 15.68/sec |
| Health Score | 980% |
| Threads | 10 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 66-67 cores)</summary>

```
1778582237 67
1778582242 67
1778582247 67
1778582252 67
1778582257 67
1778582262 67
1778582267 67
1778582272 67
1778582277 67
1778582282 67
1778582287 67
1778582292 67
1778582297 66
1778582302 66
1778582307 66
1778582312 66
1778582317 66
1778582322 66
1778582327 66
1778582332 67
```
</details>

---

