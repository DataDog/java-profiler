---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-07 12:54:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 662 |
| Sample Rate | 11.03/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 861 |
| Sample Rate | 14.35/sec |
| Health Score | 897% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 55-61 cores)</summary>

```
1775580485 61
1775580490 61
1775580495 61
1775580500 61
1775580505 61
1775580510 61
1775580515 61
1775580520 61
1775580525 61
1775580530 61
1775580535 61
1775580540 61
1775580545 61
1775580550 57
1775580555 57
1775580560 57
1775580565 57
1775580570 57
1775580575 57
1775580580 57
```
</details>

---

