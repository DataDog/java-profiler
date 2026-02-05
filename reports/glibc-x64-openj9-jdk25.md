---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-05 15:03:46 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 729 |
| Sample Rate | 12.15/sec |
| Health Score | 759% |
| Threads | 12 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1770321617 91
1770321622 91
1770321627 91
1770321632 91
1770321637 91
1770321642 91
1770321647 91
1770321652 91
1770321657 91
1770321662 91
1770321667 91
1770321672 91
1770321677 91
1770321682 91
1770321687 91
1770321692 90
1770321697 90
1770321702 90
1770321707 96
1770321712 96
```
</details>

---

