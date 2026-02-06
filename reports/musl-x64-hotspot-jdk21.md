---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-06 09:39:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (2 unique values: 27-30 cores)</summary>

```
1770388390 30
1770388395 30
1770388400 27
1770388405 27
1770388410 27
1770388415 27
1770388420 27
1770388425 27
1770388431 27
1770388436 27
1770388441 27
1770388446 27
1770388451 27
1770388456 27
1770388461 27
1770388466 27
1770388471 27
1770388476 27
1770388481 27
1770388486 27
```
</details>

---

