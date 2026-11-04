---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 09:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 344 |
| Sample Rate | 5.73/sec |
| Health Score | 358% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1793801573 81
1793801578 83
1793801583 83
1793801588 83
1793801593 83
1793801598 83
1793801603 83
1793801608 83
1793801613 83
1793801618 83
1793801623 83
1793801628 83
1793801633 83
1793801638 83
1793801643 83
1793801648 83
1793801653 83
1793801658 83
1793801663 83
1793801668 83
```
</details>

---

