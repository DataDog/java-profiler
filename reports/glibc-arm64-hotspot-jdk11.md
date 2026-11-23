---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:46:03 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 10 |
| Allocations | 179 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (4 unique values: 57-60 cores)</summary>

```
1795451819 60
1795451824 60
1795451829 58
1795451834 58
1795451839 58
1795451844 58
1795451849 58
1795451854 58
1795451859 59
1795451864 59
1795451869 59
1795451874 59
1795451879 59
1795451884 57
1795451889 57
1795451894 57
1795451899 57
1795451904 59
1795451909 59
1795451914 59
```
</details>

---

