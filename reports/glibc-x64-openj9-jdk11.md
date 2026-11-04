---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 05:58:32 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793789576 32
1793789581 32
1793789586 32
1793789591 32
1793789596 32
1793789601 32
1793789606 32
1793789611 32
1793789616 32
1793789621 32
1793789626 32
1793789631 32
1793789636 32
1793789641 32
1793789646 32
1793789651 30
1793789656 30
1793789661 30
1793789666 30
1793789671 30
```
</details>

---

