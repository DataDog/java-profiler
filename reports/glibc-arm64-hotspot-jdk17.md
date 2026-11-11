---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 13:18:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 280 |
| Sample Rate | 4.67/sec |
| Health Score | 292% |
| Threads | 10 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794420819 48
1794420824 48
1794420829 48
1794420834 48
1794420839 48
1794420844 48
1794420849 48
1794420854 48
1794420859 48
1794420864 48
1794420869 48
1794420874 48
1794420879 48
1794420884 48
1794420889 36
1794420894 36
1794420899 36
1794420904 36
1794420909 36
1794420914 36
```
</details>

---

