---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 11:55:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 84-92 cores)</summary>

```
1786636237 84
1786636242 84
1786636247 84
1786636252 84
1786636257 86
1786636262 86
1786636267 86
1786636272 86
1786636277 86
1786636282 86
1786636287 86
1786636292 86
1786636297 86
1786636302 86
1786636307 86
1786636312 86
1786636317 86
1786636322 92
1786636327 92
1786636332 90
```
</details>

---

