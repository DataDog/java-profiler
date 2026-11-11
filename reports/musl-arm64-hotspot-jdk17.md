---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 13:18:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
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
1794420909 64
1794420914 64
1794420919 64
1794420924 64
1794420929 64
1794420934 64
1794420939 64
```
</details>

---

