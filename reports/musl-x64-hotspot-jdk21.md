---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:07:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (4 unique values: 80-87 cores)</summary>

```
1795690870 80
1795690875 80
1795690880 80
1795690885 80
1795690890 80
1795690895 80
1795690900 80
1795690905 80
1795690910 80
1795690915 80
1795690920 82
1795690925 82
1795690930 82
1795690935 82
1795690940 82
1795690945 87
1795690950 87
1795690955 87
1795690960 87
1795690965 87
```
</details>

---

