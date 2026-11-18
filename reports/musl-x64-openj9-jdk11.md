---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 635 |
| Sample Rate | 10.58/sec |
| Health Score | 661% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 983 |
| Sample Rate | 16.38/sec |
| Health Score | 1024% |
| Threads | 11 |
| Allocations | 505 |

<details>
<summary>CPU Timeline (3 unique values: 82-87 cores)</summary>

```
1794999804 84
1794999809 84
1794999814 84
1794999819 84
1794999824 84
1794999829 84
1794999834 84
1794999839 84
1794999844 84
1794999849 87
1794999854 87
1794999859 87
1794999864 87
1794999869 87
1794999874 82
1794999879 82
1794999884 82
1794999889 82
1794999894 82
1794999899 82
```
</details>

---

