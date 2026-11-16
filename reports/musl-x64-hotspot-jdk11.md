---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 05:16:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (4 unique values: 54-66 cores)</summary>

```
1794823670 66
1794823675 66
1794823680 66
1794823685 54
1794823690 54
1794823695 54
1794823700 54
1794823705 54
1794823710 54
1794823715 54
1794823720 54
1794823725 54
1794823730 54
1794823735 54
1794823740 54
1794823745 54
1794823750 54
1794823755 56
1794823760 56
1794823765 60
```
</details>

---

