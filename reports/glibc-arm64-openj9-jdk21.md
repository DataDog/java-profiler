---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 05:35:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 10 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1794997829 34
1794997834 34
1794997839 34
1794997844 34
1794997849 34
1794997854 34
1794997859 34
1794997864 32
1794997869 32
1794997874 32
1794997879 32
1794997884 32
1794997889 32
1794997894 32
1794997899 32
1794997904 34
1794997909 34
1794997914 34
1794997919 34
1794997924 34
```
</details>

---

