---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-29 10:20:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 11 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793283341 64
1793283346 64
1793283351 64
1793283356 64
1793283361 64
1793283366 64
1793283371 64
1793283376 64
1793283381 64
1793283386 64
1793283391 64
1793283396 62
1793283401 62
1793283406 62
1793283411 62
1793283416 62
1793283421 62
1793283426 64
1793283431 64
1793283436 64
```
</details>

---

