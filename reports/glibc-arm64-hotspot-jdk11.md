---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-07 18:05:05 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 441 |
| Sample Rate | 7.35/sec |
| Health Score | 459% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 35-40 cores)</summary>

```
1794092411 35
1794092416 35
1794092421 35
1794092426 35
1794092431 35
1794092436 35
1794092441 35
1794092446 35
1794092451 35
1794092456 35
1794092461 35
1794092466 35
1794092471 35
1794092476 40
1794092481 40
1794092486 40
1794092491 40
1794092496 40
1794092501 40
1794092506 40
```
</details>

---

