---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-12 04:38:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 64-79 cores)</summary>

```
1786523584 69
1786523589 69
1786523594 69
1786523599 69
1786523604 64
1786523609 64
1786523614 64
1786523619 64
1786523624 64
1786523629 64
1786523634 64
1786523639 64
1786523644 64
1786523649 64
1786523654 79
1786523659 79
1786523664 79
1786523669 79
1786523674 79
1786523679 79
```
</details>

---

