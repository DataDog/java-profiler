---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:02:29 EST

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 58 |
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
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (5 unique values: 58-93 cores)</summary>

```
1794405421 72
1794405426 72
1794405431 72
1794405436 74
1794405441 74
1794405446 74
1794405451 74
1794405456 74
1794405461 74
1794405466 74
1794405471 74
1794405476 74
1794405481 74
1794405486 93
1794405491 93
1794405496 93
1794405501 93
1794405506 93
1794405511 93
1794405516 93
```
</details>

---

