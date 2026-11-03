---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:25:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 795 |
| Sample Rate | 13.25/sec |
| Health Score | 828% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 65-80 cores)</summary>

```
1793722796 65
1793722801 65
1793722806 65
1793722811 65
1793722816 65
1793722821 65
1793722826 72
1793722831 72
1793722836 72
1793722841 72
1793722846 72
1793722851 72
1793722856 72
1793722861 72
1793722866 72
1793722871 72
1793722876 72
1793722881 72
1793722886 78
1793722891 78
```
</details>

---

