---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-06 09:39:27 EST

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 454 |
| Sample Rate | 7.57/sec |
| Health Score | 473% |
| Threads | 9 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770388391 27
1770388396 27
1770388401 27
1770388406 27
1770388411 27
1770388416 27
1770388421 27
1770388426 32
1770388431 32
1770388436 32
1770388441 32
1770388446 32
1770388451 32
1770388456 32
1770388461 32
1770388466 32
1770388471 32
1770388476 32
1770388481 32
1770388486 32
```
</details>

---

