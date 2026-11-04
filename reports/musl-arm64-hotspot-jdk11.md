---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:18:51 EST

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
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1793801597 48
1793801602 48
1793801607 48
1793801612 48
1793801617 48
1793801622 48
1793801628 48
1793801633 48
1793801638 48
1793801643 48
1793801648 48
1793801653 48
1793801658 53
1793801663 53
1793801668 53
1793801673 53
1793801678 53
1793801683 53
1793801688 53
1793801693 53
```
</details>

---

