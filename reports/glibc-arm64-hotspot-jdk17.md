---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-13 13:48:08 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 9 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1794595317 48
1794595322 48
1794595327 48
1794595332 48
1794595337 48
1794595342 48
1794595347 48
1794595352 48
1794595357 48
1794595362 48
1794595367 48
1794595372 48
1794595377 48
1794595382 48
1794595387 48
1794595392 48
1794595397 48
1794595402 48
1794595407 48
1794595412 48
```
</details>

---

