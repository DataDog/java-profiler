---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 11:19:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 8 |
| Allocations | 160 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 257 |
| Sample Rate | 4.28/sec |
| Health Score | 268% |
| Threads | 13 |
| Allocations | 93 |

<details>
<summary>CPU Timeline (3 unique values: 44-64 cores)</summary>

```
1791385865 51
1791385870 51
1791385875 51
1791385880 51
1791385885 51
1791385890 64
1791385895 64
1791385900 64
1791385905 64
1791385910 64
1791385915 64
1791385920 64
1791385925 64
1791385930 64
1791385935 44
1791385940 44
1791385945 44
1791385950 44
1791385955 44
1791385960 44
```
</details>

---

