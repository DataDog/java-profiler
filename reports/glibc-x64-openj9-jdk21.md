---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 09:09:12 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 56-66 cores)</summary>

```
1790168629 56
1790168634 56
1790168639 56
1790168644 56
1790168649 56
1790168654 66
1790168659 66
1790168664 66
1790168669 66
1790168674 66
1790168679 66
1790168684 66
1790168689 66
1790168694 66
1790168699 66
1790168704 66
1790168709 61
1790168714 61
1790168719 61
1790168724 61
```
</details>

---

