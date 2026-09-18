---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:31:40 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 43-77 cores)</summary>

```
1789712745 75
1789712750 75
1789712755 75
1789712760 75
1789712765 77
1789712770 77
1789712775 77
1789712780 77
1789712785 43
1789712790 43
1789712795 43
1789712800 43
1789712805 43
1789712810 43
1789712815 45
1789712820 45
1789712825 45
1789712830 45
1789712835 45
1789712840 45
```
</details>

---

