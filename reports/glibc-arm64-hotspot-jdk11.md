---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-27 21:22:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790558260 43
1790558265 43
1790558270 43
1790558275 43
1790558280 43
1790558285 43
1790558290 43
1790558295 48
1790558300 48
1790558305 48
1790558310 48
1790558315 48
1790558320 48
1790558325 48
1790558330 48
1790558335 48
1790558340 48
1790558345 48
1790558350 48
1790558355 48
```
</details>

---

