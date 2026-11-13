---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:36:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 67-74 cores)</summary>

```
1794569589 67
1794569594 67
1794569599 67
1794569604 67
1794569609 67
1794569614 67
1794569619 67
1794569624 67
1794569629 67
1794569634 67
1794569639 67
1794569644 74
1794569649 74
1794569654 74
1794569659 74
1794569664 74
1794569669 74
1794569674 74
1794569679 74
1794569684 74
```
</details>

---

