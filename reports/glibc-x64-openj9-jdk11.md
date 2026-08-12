---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 04:38:14 EDT

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
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1786523603 61
1786523608 61
1786523613 61
1786523618 61
1786523623 61
1786523628 61
1786523633 59
1786523638 59
1786523643 59
1786523648 59
1786523653 59
1786523658 59
1786523663 59
1786523668 59
1786523673 61
1786523678 61
1786523683 61
1786523688 61
1786523693 61
1786523698 61
```
</details>

---

