---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 09:14:00 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 866 |
| Sample Rate | 14.43/sec |
| Health Score | 902% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 65-71 cores)</summary>

```
1794319711 65
1794319716 69
1794319721 69
1794319726 69
1794319731 69
1794319736 69
1794319741 69
1794319746 71
1794319751 71
1794319756 71
1794319761 71
1794319766 71
1794319771 71
1794319776 71
1794319781 71
1794319786 71
1794319791 71
1794319796 71
1794319801 71
1794319806 71
```
</details>

---

