---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 10:44:20 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 562 |
| Sample Rate | 9.37/sec |
| Health Score | 586% |
| Threads | 12 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 88-92 cores)</summary>

```
1794584418 92
1794584423 92
1794584428 92
1794584433 92
1794584438 90
1794584443 90
1794584448 90
1794584453 90
1794584458 88
1794584463 88
1794584468 88
1794584473 88
1794584478 88
1794584483 88
1794584488 88
1794584493 88
1794584498 88
1794584503 88
1794584508 88
1794584513 88
```
</details>

---

