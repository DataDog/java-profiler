---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-22 11:52:08 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1186 |
| Sample Rate | 19.77/sec |
| Health Score | 1236% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1790091751 85
1790091756 85
1790091761 85
1790091766 85
1790091771 85
1790091776 83
1790091781 83
1790091786 85
1790091791 85
1790091796 85
1790091801 83
1790091806 83
1790091811 83
1790091816 83
1790091821 83
1790091826 83
1790091831 83
1790091836 83
1790091841 83
1790091846 83
```
</details>

---

