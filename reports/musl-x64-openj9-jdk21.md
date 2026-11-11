---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 06:35:25 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 717 |
| Sample Rate | 11.95/sec |
| Health Score | 747% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 67-72 cores)</summary>

```
1794396619 70
1794396624 70
1794396629 70
1794396634 70
1794396639 68
1794396645 68
1794396650 68
1794396655 68
1794396660 68
1794396665 68
1794396670 72
1794396675 72
1794396680 72
1794396685 68
1794396690 68
1794396695 68
1794396700 68
1794396705 68
1794396710 68
1794396715 68
```
</details>

---

