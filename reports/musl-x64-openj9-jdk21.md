---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:05:04 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 895 |
| Sample Rate | 14.92/sec |
| Health Score | 932% |
| Threads | 10 |
| Allocations | 451 |

<details>
<summary>CPU Timeline (3 unique values: 79-83 cores)</summary>

```
1795449491 81
1795449496 83
1795449501 83
1795449506 83
1795449511 83
1795449516 83
1795449521 81
1795449526 81
1795449531 81
1795449536 81
1795449541 81
1795449546 81
1795449551 81
1795449556 81
1795449561 81
1795449566 81
1795449571 81
1795449576 81
1795449581 81
1795449586 79
```
</details>

---

