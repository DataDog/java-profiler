---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-01-30 05:41:42 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 25-32 cores)</summary>

```
1769769340 32
1769769345 32
1769769350 32
1769769355 32
1769769360 32
1769769365 27
1769769370 27
1769769375 27
1769769380 27
1769769385 27
1769769390 27
1769769395 27
1769769400 27
1769769405 27
1769769410 27
1769769415 27
1769769420 27
1769769425 27
1769769430 27
1769769435 27
```
</details>

---

