---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-29 12:24:45 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 452 |

<details>
<summary>CPU Timeline (5 unique values: 69-79 cores)</summary>

```
1777479496 73
1777479501 75
1777479506 75
1777479511 75
1777479516 75
1777479521 75
1777479526 75
1777479531 75
1777479536 71
1777479541 71
1777479546 71
1777479551 71
1777479556 71
1777479561 71
1777479566 71
1777479571 71
1777479576 73
1777479581 73
1777479586 69
1777479591 69
```
</details>

---

