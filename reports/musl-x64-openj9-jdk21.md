---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-26 06:07:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1795690865 29
1795690870 29
1795690875 29
1795690880 29
1795690885 29
1795690890 29
1795690895 32
1795690900 32
1795690905 32
1795690910 32
1795690915 32
1795690920 32
1795690925 32
1795690930 32
1795690935 32
1795690940 32
1795690945 32
1795690950 32
1795690955 32
1795690960 32
```
</details>

---

