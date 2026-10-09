---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-09 03:28:10 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 391 |
| Sample Rate | 6.52/sec |
| Health Score | 407% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1791530623 12
1791530628 12
1791530633 12
1791530638 12
1791530643 12
1791530648 32
1791530653 32
1791530658 32
1791530663 32
1791530668 32
1791530673 32
1791530678 32
1791530683 32
1791530688 32
1791530693 32
1791530698 32
1791530703 32
1791530708 32
1791530713 32
1791530718 32
```
</details>

---

