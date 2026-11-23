---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-23 04:44:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 370 |
| Sample Rate | 6.17/sec |
| Health Score | 386% |
| Threads | 14 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795426819 49
1795426824 49
1795426829 49
1795426834 49
1795426839 49
1795426844 49
1795426849 44
1795426854 44
1795426859 44
1795426864 44
1795426869 44
1795426874 44
1795426879 44
1795426884 44
1795426889 49
1795426894 49
1795426899 49
1795426904 49
1795426909 49
1795426914 49
```
</details>

---

