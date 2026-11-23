---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:58:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (4 unique values: 54-58 cores)</summary>

```
1795452836 54
1795452841 54
1795452846 54
1795452851 54
1795452856 54
1795452861 54
1795452866 54
1795452871 56
1795452876 56
1795452881 54
1795452886 54
1795452891 54
1795452896 56
1795452901 56
1795452906 56
1795452911 56
1795452916 58
1795452921 58
1795452926 58
1795452931 58
```
</details>

---

