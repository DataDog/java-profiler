---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 09:18:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 380 |
| Sample Rate | 6.33/sec |
| Health Score | 396% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (5 unique values: 42-48 cores)</summary>

```
1793801559 48
1793801564 48
1793801569 48
1793801574 47
1793801579 47
1793801584 47
1793801589 47
1793801594 46
1793801599 46
1793801604 47
1793801609 47
1793801614 42
1793801619 42
1793801624 43
1793801629 43
1793801634 43
1793801639 42
1793801644 42
1793801650 42
1793801655 42
```
</details>

---

