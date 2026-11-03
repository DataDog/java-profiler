---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 14:44:30 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 28-51 cores)</summary>

```
1793734697 29
1793734702 29
1793734707 29
1793734712 29
1793734717 51
1793734722 51
1793734727 28
1793734732 28
1793734737 28
1793734742 28
1793734747 28
1793734752 28
1793734757 28
1793734762 28
1793734767 28
1793734772 28
1793734777 30
1793734782 30
1793734787 30
1793734792 30
```
</details>

---

