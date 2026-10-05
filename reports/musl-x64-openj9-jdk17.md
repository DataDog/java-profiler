---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-05 05:22:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 32-56 cores)</summary>

```
1791191791 52
1791191796 52
1791191801 52
1791191806 52
1791191811 52
1791191816 52
1791191821 52
1791191826 56
1791191831 56
1791191836 56
1791191841 56
1791191846 56
1791191851 56
1791191856 56
1791191861 40
1791191867 40
1791191872 40
1791191877 40
1791191882 32
1791191887 32
```
</details>

---

