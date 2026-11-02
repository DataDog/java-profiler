---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-02 17:11:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1793656897 70
1793656902 70
1793656908 70
1793656913 70
1793656918 72
1793656923 72
1793656928 72
1793656933 72
1793656938 72
1793656943 72
1793656948 72
1793656953 72
1793656958 72
1793656963 72
1793656968 72
1793656973 72
1793656978 72
1793656983 72
1793656988 72
1793656993 72
```
</details>

---

