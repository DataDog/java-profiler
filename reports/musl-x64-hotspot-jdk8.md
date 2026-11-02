---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-02 07:22:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 215 |
| Sample Rate | 3.58/sec |
| Health Score | 224% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 48-73 cores)</summary>

```
1793621944 48
1793621949 60
1793621954 60
1793621959 60
1793621964 60
1793621969 60
1793621974 60
1793621979 60
1793621984 60
1793621989 60
1793621994 60
1793621999 60
1793622004 60
1793622009 69
1793622014 69
1793622019 69
1793622024 71
1793622029 71
1793622034 73
1793622039 73
```
</details>

---

