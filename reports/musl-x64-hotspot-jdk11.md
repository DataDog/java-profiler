---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-14 05:49:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 571 |
| Sample Rate | 9.52/sec |
| Health Score | 595% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 718 |
| Sample Rate | 11.97/sec |
| Health Score | 748% |
| Threads | 8 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 66-74 cores)</summary>

```
1786700599 74
1786700604 74
1786700609 66
1786700614 66
1786700619 66
1786700624 66
1786700629 66
1786700634 66
1786700639 66
1786700644 66
1786700649 66
1786700654 66
1786700659 66
1786700664 66
1786700669 66
1786700674 66
1786700679 66
1786700684 66
1786700689 66
1786700694 66
```
</details>

---

