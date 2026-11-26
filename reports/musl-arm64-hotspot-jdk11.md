---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 09:25:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 14 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795702839 64
1795702844 64
1795702849 64
1795702854 64
1795702859 64
1795702864 64
1795702869 64
1795702874 64
1795702879 64
1795702884 64
1795702889 64
1795702894 64
1795702899 64
1795702904 64
1795702909 64
1795702914 64
1795702919 64
1795702924 64
1795702929 64
1795702934 64
```
</details>

---

