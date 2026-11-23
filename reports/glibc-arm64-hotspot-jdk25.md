---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:46:03 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 13 |
| Allocations | 114 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795451849 34
1795451854 29
1795451859 29
1795451864 29
1795451869 29
1795451874 29
1795451879 29
1795451884 29
1795451889 29
1795451894 29
1795451899 29
1795451904 29
1795451909 29
1795451914 29
1795451919 29
1795451924 34
1795451929 34
1795451934 34
1795451939 34
1795451944 34
```
</details>

---

