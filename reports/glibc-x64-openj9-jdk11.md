---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:36:49 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1794569559 89
1794569564 89
1794569569 89
1794569574 89
1794569579 89
1794569584 89
1794569589 91
1794569594 91
1794569599 91
1794569604 91
1794569609 91
1794569614 91
1794569619 91
1794569624 91
1794569629 91
1794569634 91
1794569639 91
1794569644 91
1794569649 91
1794569654 91
```
</details>

---

