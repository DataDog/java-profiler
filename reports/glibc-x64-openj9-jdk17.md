---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:18:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 856 |
| Sample Rate | 14.27/sec |
| Health Score | 892% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 67-80 cores)</summary>

```
1795529686 67
1795529691 67
1795529696 67
1795529701 67
1795529706 67
1795529711 67
1795529716 67
1795529721 67
1795529726 67
1795529731 67
1795529736 67
1795529741 76
1795529746 76
1795529751 76
1795529756 76
1795529761 76
1795529766 76
1795529771 76
1795529776 76
1795529781 78
```
</details>

---

