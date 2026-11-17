---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 13:29:09 EST

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 501 |
| Sample Rate | 8.35/sec |
| Health Score | 522% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1794939901 25
1794939906 25
1794939911 25
1794939916 25
1794939921 25
1794939926 25
1794939931 25
1794939936 25
1794939941 25
1794939946 25
1794939951 25
1794939956 25
1794939961 27
1794939966 27
1794939971 27
1794939976 27
1794939981 25
1794939986 25
1794939991 25
1794939996 25
```
</details>

---

