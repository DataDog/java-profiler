---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 09:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 11 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (2 unique values: 13-30 cores)</summary>

```
1793801619 13
1793801624 13
1793801629 13
1793801634 13
1793801639 13
1793801644 13
1793801649 30
1793801654 30
1793801659 30
1793801664 30
1793801669 30
1793801674 30
1793801679 30
1793801684 30
1793801689 30
1793801694 30
1793801699 30
1793801704 30
1793801709 30
1793801714 30
```
</details>

---

