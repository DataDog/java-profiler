---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 15:03:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 7 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 10 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794340604 51
1794340609 51
1794340614 46
1794340619 46
1794340624 46
1794340629 46
1794340634 46
1794340639 46
1794340644 46
1794340649 46
1794340654 46
1794340659 46
1794340664 46
1794340669 46
1794340674 46
1794340679 46
1794340684 46
1794340689 46
1794340694 46
1794340699 46
```
</details>

---

