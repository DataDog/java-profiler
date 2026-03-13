---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-03-13 07:08:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 10 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 13 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (3 unique values: 47-56 cores)</summary>

```
1773399800 51
1773399805 51
1773399810 51
1773399815 51
1773399820 47
1773399825 47
1773399830 47
1773399836 47
1773399841 47
1773399846 47
1773399851 47
1773399856 47
1773399861 47
1773399866 47
1773399871 47
1773399876 47
1773399881 47
1773399886 47
1773399891 47
1773399896 47
```
</details>

---

