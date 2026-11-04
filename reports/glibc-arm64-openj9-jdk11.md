---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 09:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793801569 46
1793801574 48
1793801579 48
1793801584 48
1793801589 48
1793801594 48
1793801599 48
1793801604 48
1793801609 48
1793801614 48
1793801619 48
1793801624 48
1793801629 48
1793801634 46
1793801639 46
1793801644 46
1793801649 46
1793801654 46
1793801659 46
1793801664 46
```
</details>

---

