---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:59:18 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 21-32 cores)</summary>

```
1770828851 32
1770828856 32
1770828861 32
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
1770828916 32
1770828921 30
1770828926 30
1770828931 28
1770828936 28
1770828941 30
1770828946 30
```
</details>

---

