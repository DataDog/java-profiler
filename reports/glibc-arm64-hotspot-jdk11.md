---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 13:18:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 866 |
| Sample Rate | 14.43/sec |
| Health Score | 902% |
| Threads | 9 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794420824 51
1794420829 51
1794420834 51
1794420839 51
1794420844 51
1794420849 51
1794420854 51
1794420859 64
1794420864 64
1794420869 64
1794420874 64
1794420879 64
1794420884 64
1794420889 64
1794420894 64
1794420899 64
1794420904 64
1794420909 51
1794420914 51
1794420919 51
```
</details>

---

