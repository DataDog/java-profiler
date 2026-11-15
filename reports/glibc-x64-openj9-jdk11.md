---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 18:02:45 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 10 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (4 unique values: 79-91 cores)</summary>

```
1794783544 79
1794783549 79
1794783554 81
1794783559 81
1794783564 81
1794783569 81
1794783574 81
1794783579 81
1794783584 81
1794783589 81
1794783594 81
1794783599 81
1794783604 81
1794783609 81
1794783614 89
1794783619 89
1794783624 89
1794783629 91
1794783634 91
1794783639 91
```
</details>

---

