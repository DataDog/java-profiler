---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 06:08:13 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 617 |
| Sample Rate | 10.28/sec |
| Health Score | 642% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (2 unique values: 81-83 cores)</summary>

```
1794567801 81
1794567806 81
1794567811 81
1794567816 81
1794567821 81
1794567826 81
1794567831 81
1794567836 81
1794567841 83
1794567846 83
1794567851 83
1794567856 83
1794567861 83
1794567866 83
1794567871 83
1794567876 83
1794567881 83
1794567886 83
1794567891 83
1794567896 83
```
</details>

---

