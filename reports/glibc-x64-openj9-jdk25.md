---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-13 11:08:22 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 350 |
| Sample Rate | 5.83/sec |
| Health Score | 364% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 523 |
| Sample Rate | 8.72/sec |
| Health Score | 545% |
| Threads | 11 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (2 unique values: 58-77 cores)</summary>

```
1778684535 58
1778684540 58
1778684545 58
1778684550 58
1778684555 58
1778684560 58
1778684565 58
1778684570 77
1778684575 77
1778684580 77
1778684585 77
1778684590 77
1778684595 77
1778684600 77
1778684605 77
1778684610 77
1778684615 77
1778684620 77
1778684625 77
1778684630 77
```
</details>

---

