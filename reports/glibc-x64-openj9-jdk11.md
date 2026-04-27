---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-26 21:17:46 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (4 unique values: 61-66 cores)</summary>

```
1777252390 61
1777252395 66
1777252400 66
1777252405 66
1777252410 66
1777252415 66
1777252420 66
1777252425 66
1777252430 64
1777252435 64
1777252440 66
1777252445 66
1777252450 66
1777252455 61
1777252460 61
1777252465 61
1777252470 61
1777252475 61
1777252480 61
1777252485 61
```
</details>

---

