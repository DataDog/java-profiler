---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 10:25:43 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 122 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 300 |
| Sample Rate | 5.00/sec |
| Health Score | 312% |
| Threads | 13 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (3 unique values: 37-39 cores)</summary>

```
1795015304 38
1795015309 38
1795015314 38
1795015319 38
1795015324 38
1795015329 39
1795015334 39
1795015339 39
1795015344 39
1795015349 39
1795015354 39
1795015359 39
1795015364 39
1795015369 39
1795015374 39
1795015379 39
1795015384 39
1795015389 37
1795015394 37
1795015399 37
```
</details>

---

