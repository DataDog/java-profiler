---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 09:54:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1786974668 28
1786974673 28
1786974678 30
1786974683 30
1786974688 30
1786974693 30
1786974698 30
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
1786974763 30
```
</details>

---

