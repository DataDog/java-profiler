---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 13:24:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 929 |
| Sample Rate | 15.48/sec |
| Health Score | 967% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 83-87 cores)</summary>

```
1791911932 83
1791911937 83
1791911942 83
1791911947 83
1791911952 83
1791911957 83
1791911963 85
1791911968 85
1791911973 85
1791911978 85
1791911983 85
1791911988 87
1791911993 87
1791911998 87
1791912003 87
1791912008 87
1791912013 87
1791912018 87
1791912023 87
1791912028 87
```
</details>

---

