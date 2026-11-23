---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-23 04:44:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 12-22 cores)</summary>

```
1795426819 22
1795426824 22
1795426829 22
1795426834 22
1795426839 22
1795426844 22
1795426849 22
1795426854 22
1795426859 22
1795426864 22
1795426869 22
1795426874 22
1795426879 22
1795426884 22
1795426889 22
1795426894 12
1795426899 12
1795426904 12
1795426909 12
1795426914 12
```
</details>

---

