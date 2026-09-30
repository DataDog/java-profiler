---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 08:37:23 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 10 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1790771578 64
1790771583 64
1790771588 64
1790771593 64
1790771598 64
1790771603 64
1790771608 51
1790771613 51
1790771618 51
1790771623 51
1790771628 51
1790771633 51
1790771638 51
1790771643 51
1790771648 51
1790771653 51
1790771658 51
1790771663 51
1790771668 51
1790771673 51
```
</details>

---

