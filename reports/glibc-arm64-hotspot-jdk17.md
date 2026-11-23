---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 17:14:13 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795471774 33
1795471779 33
1795471784 33
1795471789 33
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
```
</details>

---

