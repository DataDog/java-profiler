---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 08:22:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 736 |
| Sample Rate | 12.27/sec |
| Health Score | 767% |
| Threads | 11 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 63-70 cores)</summary>

```
1795007902 63
1795007907 63
1795007912 63
1795007917 63
1795007922 63
1795007927 63
1795007932 63
1795007937 68
1795007942 68
1795007947 70
1795007952 70
1795007957 70
1795007962 70
1795007967 70
1795007972 70
1795007977 70
1795007982 70
1795007987 70
1795007992 70
1795007997 70
```
</details>

---

