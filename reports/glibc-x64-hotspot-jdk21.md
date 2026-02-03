---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 10:07:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 14-19 cores)</summary>

```
1770130801 18
1770130806 18
1770130811 18
1770130816 18
1770130821 18
1770130826 18
1770130831 16
1770130836 16
1770130841 16
1770130846 16
1770130851 16
1770130856 16
1770130861 16
1770130866 14
1770130871 14
1770130876 14
1770130881 14
1770130886 14
1770130891 14
1770130896 14
```
</details>

---

