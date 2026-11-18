---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:06:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 10 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 44-58 cores)</summary>

```
1795010501 58
1795010506 58
1795010511 58
1795010516 56
1795010521 56
1795010526 56
1795010531 56
1795010536 56
1795010541 56
1795010546 56
1795010551 56
1795010556 56
1795010561 56
1795010566 56
1795010571 56
1795010576 47
1795010581 47
1795010586 44
1795010591 44
1795010596 44
```
</details>

---

