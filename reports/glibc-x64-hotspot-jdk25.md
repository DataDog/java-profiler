---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-11 11:59:18 EST

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 774 |
| Sample Rate | 12.90/sec |
| Health Score | 806% |
| Threads | 9 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (3 unique values: 14-32 cores)</summary>

```
1770828851 23
1770828856 23
1770828861 23
1770828866 32
1770828871 32
1770828876 32
1770828881 32
1770828886 32
1770828891 32
1770828896 32
1770828901 32
1770828906 32
1770828911 32
1770828916 23
1770828921 23
1770828926 23
1770828931 23
1770828936 23
1770828941 23
1770828946 23
```
</details>

---

