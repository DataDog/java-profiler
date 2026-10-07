---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 01:56:52 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791352351 48
1791352356 48
1791352361 43
1791352366 43
1791352371 43
1791352376 43
1791352381 43
1791352386 43
1791352391 43
1791352396 43
1791352401 43
1791352406 43
1791352411 43
1791352416 43
1791352421 48
1791352426 48
1791352431 48
1791352436 48
1791352441 48
1791352446 48
```
</details>

---

