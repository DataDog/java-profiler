---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 09:25:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795702814 33
1795702819 33
1795702824 33
1795702829 33
1795702834 33
1795702839 33
1795702844 33
1795702849 33
1795702854 33
1795702859 33
1795702864 33
1795702869 33
1795702874 33
1795702879 33
1795702884 33
1795702889 33
1795702894 33
1795702899 33
1795702904 33
1795702909 33
```
</details>

---

