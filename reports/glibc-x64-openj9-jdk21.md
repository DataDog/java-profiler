---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 11:11:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 10 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 12 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (4 unique values: 60-96 cores)</summary>

```
1770134716 89
1770134721 89
1770134726 89
1770134731 89
1770134736 89
1770134741 89
1770134746 89
1770134751 89
1770134756 89
1770134761 89
1770134766 92
1770134771 92
1770134776 96
1770134781 96
1770134786 96
1770134791 96
1770134796 96
1770134801 96
1770134806 96
1770134811 96
```
</details>

---

