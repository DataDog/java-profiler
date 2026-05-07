---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-07 10:58:43 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 421 |
| Sample Rate | 7.02/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (8 unique values: 64-82 cores)</summary>

```
1778165644 80
1778165649 82
1778165654 82
1778165659 82
1778165664 82
1778165669 71
1778165674 71
1778165679 71
1778165684 65
1778165689 65
1778165694 65
1778165699 65
1778165704 65
1778165709 64
1778165714 64
1778165719 64
1778165725 66
1778165730 66
1778165735 66
1778165740 66
```
</details>

---

