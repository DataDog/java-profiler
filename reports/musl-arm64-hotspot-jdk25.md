---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-07 18:05:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1794092416 29
1794092421 29
1794092426 29
1794092431 29
1794092436 29
1794092441 29
1794092446 29
1794092451 29
1794092456 29
1794092461 29
1794092466 24
1794092471 24
1794092476 24
1794092481 24
1794092486 24
1794092491 24
1794092496 24
1794092501 24
1794092506 24
1794092512 24
```
</details>

---

