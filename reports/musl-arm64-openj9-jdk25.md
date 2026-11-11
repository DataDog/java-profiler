---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 13:18:18 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 9 |
| Allocations | 157 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1794420804 40
1794420809 40
1794420814 40
1794420819 40
1794420824 40
1794420829 40
1794420834 40
1794420839 40
1794420844 40
1794420849 40
1794420854 40
1794420859 40
1794420864 40
1794420869 40
1794420874 40
1794420879 40
1794420884 40
1794420889 40
1794420894 40
1794420899 40
```
</details>

---

