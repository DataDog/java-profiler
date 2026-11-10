---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:59:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (4 unique values: 27-65 cores)</summary>

```
1794311735 27
1794311740 27
1794311745 27
1794311750 27
1794311755 27
1794311760 27
1794311765 27
1794311770 27
1794311775 27
1794311780 27
1794311785 49
1794311790 49
1794311795 49
1794311800 49
1794311805 43
1794311810 43
1794311815 43
1794311820 43
1794311825 43
1794311830 43
```
</details>

---

