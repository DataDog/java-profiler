---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-20 08:52:04 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 11 |
| Allocations | 159 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1795182376 24
1795182381 24
1795182386 24
1795182391 24
1795182396 24
1795182401 24
1795182406 24
1795182411 24
1795182416 24
1795182421 24
1795182426 24
1795182431 24
1795182436 24
1795182441 24
1795182446 24
1795182451 24
1795182456 24
1795182461 29
1795182466 29
1795182471 29
```
</details>

---

