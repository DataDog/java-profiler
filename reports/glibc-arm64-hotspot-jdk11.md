---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:44:21 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 9 |
| Allocations | 173 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795426821 49
1795426826 49
1795426831 49
1795426836 49
1795426841 49
1795426846 49
1795426851 44
1795426856 44
1795426861 44
1795426866 44
1795426871 44
1795426876 44
1795426881 44
1795426886 44
1795426891 49
1795426896 49
1795426901 49
1795426906 49
1795426911 49
1795426916 49
```
</details>

---

