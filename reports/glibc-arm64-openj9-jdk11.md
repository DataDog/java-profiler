---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-08 14:27:51 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794165854 38
1794165859 43
1794165864 43
1794165869 38
1794165874 38
1794165879 38
1794165884 38
1794165889 38
1794165894 38
1794165899 38
1794165904 38
1794165909 38
1794165914 38
1794165919 43
1794165924 43
1794165929 43
1794165934 43
1794165939 43
1794165944 38
1794165949 38
```
</details>

---

