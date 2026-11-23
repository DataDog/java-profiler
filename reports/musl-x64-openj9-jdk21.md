---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 06:55:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (2 unique values: 66-75 cores)</summary>

```
1795434622 75
1795434627 75
1795434632 66
1795434637 66
1795434642 66
1795434647 66
1795434653 66
1795434658 66
1795434663 66
1795434668 66
1795434673 66
1795434678 66
1795434683 66
1795434688 66
1795434693 66
1795434698 66
1795434703 66
1795434708 66
1795434713 66
1795434718 66
```
</details>

---

