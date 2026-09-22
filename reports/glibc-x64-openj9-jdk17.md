---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 09:50:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 9 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (2 unique values: 12-48 cores)</summary>

```
1790084745 12
1790084750 12
1790084755 12
1790084760 12
1790084765 12
1790084770 48
1790084775 48
1790084780 48
1790084785 48
1790084790 48
1790084795 48
1790084800 48
1790084805 48
1790084810 48
1790084815 48
1790084820 48
1790084825 48
1790084830 48
1790084835 48
1790084840 48
```
</details>

---

