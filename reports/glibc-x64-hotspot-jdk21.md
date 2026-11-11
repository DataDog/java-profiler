---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 18:52:59 EST

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 428 |
| Sample Rate | 7.13/sec |
| Health Score | 446% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 10-32 cores)</summary>

```
1794440890 11
1794440895 11
1794440900 11
1794440905 32
1794440910 32
1794440915 32
1794440920 32
1794440925 32
1794440931 32
1794440936 32
1794440941 32
1794440946 32
1794440951 32
1794440956 32
1794440961 32
1794440966 32
1794440971 32
1794440976 32
1794440981 32
1794440986 32
```
</details>

---

