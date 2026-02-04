---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 14:09:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 11 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1201 |
| Sample Rate | 20.02/sec |
| Health Score | 1251% |
| Threads | 15 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 83-90 cores)</summary>

```
1770231817 87
1770231822 87
1770231827 87
1770231832 87
1770231837 87
1770231842 87
1770231847 87
1770231852 90
1770231857 90
1770231862 90
1770231867 90
1770231872 90
1770231877 90
1770231882 90
1770231887 85
1770231892 85
1770231897 85
1770231902 83
1770231907 83
1770231912 83
```
</details>

---

