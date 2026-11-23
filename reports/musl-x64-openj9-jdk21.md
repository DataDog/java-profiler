---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:44:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 15.35/sec |
| Health Score | 959% |
| Threads | 10 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (4 unique values: 37-47 cores)</summary>

```
1795426784 39
1795426789 39
1795426794 39
1795426799 39
1795426804 39
1795426809 39
1795426814 39
1795426819 37
1795426824 37
1795426829 45
1795426834 45
1795426839 45
1795426844 45
1795426849 45
1795426854 45
1795426859 45
1795426864 45
1795426869 47
1795426874 47
1795426879 47
```
</details>

---

