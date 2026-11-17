---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 11:12:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 716 |
| Sample Rate | 11.93/sec |
| Health Score | 746% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (4 unique values: 73-78 cores)</summary>

```
1794931678 77
1794931683 77
1794931688 73
1794931693 73
1794931698 73
1794931703 73
1794931708 73
1794931713 75
1794931718 75
1794931723 75
1794931728 75
1794931733 75
1794931738 75
1794931743 75
1794931748 75
1794931753 78
1794931758 78
1794931763 78
1794931768 78
1794931773 78
```
</details>

---

