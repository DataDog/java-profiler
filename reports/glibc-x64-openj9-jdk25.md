---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-28 12:39:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1793205354 91
1793205359 91
1793205364 89
1793205369 89
1793205374 89
1793205379 89
1793205384 89
1793205389 89
1793205394 89
1793205399 89
1793205404 89
1793205409 89
1793205414 89
1793205419 89
1793205424 89
1793205429 89
1793205434 89
1793205439 89
1793205444 89
1793205449 89
```
</details>

---

