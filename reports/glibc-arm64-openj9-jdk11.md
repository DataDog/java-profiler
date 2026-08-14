---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-14 05:49:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 7 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 49-64 cores)</summary>

```
1786700770 64
1786700775 64
1786700780 64
1786700785 64
1786700790 64
1786700795 64
1786700800 64
1786700805 64
1786700810 64
1786700815 64
1786700820 64
1786700825 64
1786700830 59
1786700835 59
1786700840 59
1786700845 59
1786700850 59
1786700855 54
1786700860 54
1786700865 54
```
</details>

---

