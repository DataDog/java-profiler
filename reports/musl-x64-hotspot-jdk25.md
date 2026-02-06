---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-06 09:39:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 10 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 778 |
| Sample Rate | 12.97/sec |
| Health Score | 811% |
| Threads | 11 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1770388396 32
1770388401 32
1770388406 32
1770388411 32
1770388416 32
1770388421 32
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
1770388486 27
1770388491 27
```
</details>

---

