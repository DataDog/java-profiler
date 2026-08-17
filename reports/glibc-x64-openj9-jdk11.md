---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 09:54:52 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 469 |
| Sample Rate | 7.82/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 620 |
| Sample Rate | 10.33/sec |
| Health Score | 646% |
| Threads | 8 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786974678 30
1786974683 30
1786974688 30
1786974693 32
1786974698 32
1786974703 32
1786974708 32
1786974713 32
1786974718 32
1786974723 32
1786974728 32
1786974733 32
1786974738 32
1786974743 32
1786974748 32
1786974753 32
1786974758 32
1786974763 32
1786974768 32
1786974773 32
```
</details>

---

