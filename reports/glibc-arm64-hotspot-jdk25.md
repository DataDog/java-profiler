---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 17:14:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 9 |
| Allocations | 147 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795471794 33
1795471799 33
1795471804 33
1795471809 33
1795471814 33
1795471819 33
1795471824 64
1795471829 64
1795471834 64
1795471839 64
1795471844 64
1795471849 64
1795471854 64
1795471859 64
1795471864 64
1795471869 64
1795471874 64
1795471879 64
1795471884 64
1795471889 64
```
</details>

---

