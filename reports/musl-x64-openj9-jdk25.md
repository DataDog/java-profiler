---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:09:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 426 |
| Sample Rate | 7.10/sec |
| Health Score | 444% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 51-73 cores)</summary>

```
1790168619 51
1790168624 73
1790168629 73
1790168634 68
1790168639 68
1790168644 68
1790168649 68
1790168654 68
1790168659 68
1790168664 68
1790168669 68
1790168674 68
1790168679 68
1790168684 68
1790168689 68
1790168694 68
1790168699 68
1790168704 68
1790168709 68
1790168714 68
```
</details>

---

