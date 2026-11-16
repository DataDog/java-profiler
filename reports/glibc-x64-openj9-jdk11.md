---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:38:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (4 unique values: 45-78 cores)</summary>

```
1794832443 45
1794832448 45
1794832453 45
1794832458 45
1794832463 45
1794832468 45
1794832473 45
1794832478 45
1794832483 45
1794832488 45
1794832493 45
1794832498 45
1794832503 45
1794832508 78
1794832513 78
1794832518 59
1794832523 59
1794832528 57
1794832533 57
1794832538 57
```
</details>

---

