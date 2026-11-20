---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:39:27 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 318 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 12 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (3 unique values: 63-70 cores)</summary>

```
1795196105 68
1795196110 68
1795196115 68
1795196120 68
1795196125 68
1795196130 70
1795196135 70
1795196140 70
1795196145 70
1795196150 70
1795196155 70
1795196160 68
1795196165 68
1795196170 68
1795196175 68
1795196180 68
1795196185 68
1795196190 68
1795196195 68
1795196200 68
```
</details>

---

