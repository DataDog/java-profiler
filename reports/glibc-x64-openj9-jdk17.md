---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-24 08:33:44 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 16-21 cores)</summary>

```
1777033649 21
1777033654 21
1777033659 21
1777033664 21
1777033669 21
1777033674 16
1777033679 16
1777033684 16
1777033689 16
1777033694 16
1777033700 16
1777033705 16
1777033710 16
1777033715 16
1777033720 16
1777033725 16
1777033730 16
1777033735 16
1777033740 16
1777033745 16
```
</details>

---

