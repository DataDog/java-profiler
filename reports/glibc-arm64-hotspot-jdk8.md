---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-16 13:04:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 5 |
| Sample Rate | 0.08/sec |
| Health Score | 5% |
| Threads | 3 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 38-40 cores)</summary>

```
1794851865 40
1794851870 40
1794851875 39
1794851880 39
1794851885 39
1794851890 39
1794851895 39
1794851900 39
1794851905 39
1794851910 39
1794851915 39
1794851921 39
1794851926 39
1794851931 38
1794851936 38
1794851941 38
1794851946 38
1794851951 38
1794851956 38
1794851961 38
```
</details>

---

