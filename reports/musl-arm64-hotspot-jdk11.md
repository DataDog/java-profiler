---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 21:05:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 11 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793930474 48
1793930479 48
1793930484 48
1793930489 48
1793930494 48
1793930499 48
1793930504 48
1793930509 48
1793930514 48
1793930519 48
1793930524 48
1793930529 48
1793930534 48
1793930539 48
1793930544 48
1793930549 48
1793930554 48
1793930559 48
1793930564 48
1793930569 48
```
</details>

---

