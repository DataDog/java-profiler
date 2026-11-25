---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 12:01:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 12 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795625861 47
1795625866 47
1795625871 47
1795625876 47
1795625881 47
1795625886 47
1795625891 47
1795625896 47
1795625901 47
1795625906 47
1795625911 47
1795625916 47
1795625921 47
1795625926 47
1795625931 47
1795625936 47
1795625941 47
1795625946 47
1795625951 47
1795625956 47
```
</details>

---

