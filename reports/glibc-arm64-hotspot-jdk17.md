---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 10:25:43 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 11 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (2 unique values: 33-38 cores)</summary>

```
1795015312 33
1795015317 33
1795015322 33
1795015327 33
1795015332 33
1795015337 33
1795015342 33
1795015347 33
1795015352 33
1795015357 33
1795015362 33
1795015367 33
1795015372 33
1795015377 33
1795015382 33
1795015387 33
1795015392 38
1795015397 38
1795015402 38
1795015407 38
```
</details>

---

