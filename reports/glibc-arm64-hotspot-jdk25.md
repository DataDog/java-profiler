---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:23:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 17-29 cores)</summary>

```
1795007901 17
1795007906 17
1795007911 17
1795007917 17
1795007922 17
1795007927 17
1795007932 17
1795007937 29
1795007942 29
1795007947 29
1795007952 29
1795007957 29
1795007962 29
1795007967 29
1795007972 29
1795007977 29
1795007982 29
1795007987 29
1795007992 29
1795007997 29
```
</details>

---

