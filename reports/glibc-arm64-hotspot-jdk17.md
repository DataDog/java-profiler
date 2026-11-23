---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:58:19 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 31 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795452861 29
1795452866 29
1795452871 29
1795452876 34
1795452881 34
1795452886 34
1795452891 34
1795452896 34
1795452901 34
1795452906 34
1795452911 34
1795452916 34
1795452921 34
1795452926 34
1795452931 34
1795452936 34
1795452941 34
1795452946 34
1795452951 34
1795452956 34
```
</details>

---

