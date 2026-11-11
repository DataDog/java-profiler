---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 16:04:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 309 |
| Sample Rate | 5.15/sec |
| Health Score | 322% |
| Threads | 13 |
| Allocations | 179 |

<details>
<summary>CPU Timeline (2 unique values: 25-38 cores)</summary>

```
1794430824 25
1794430829 25
1794430834 25
1794430839 25
1794430844 25
1794430849 25
1794430854 25
1794430859 25
1794430864 25
1794430869 25
1794430874 25
1794430879 25
1794430884 25
1794430889 25
1794430894 25
1794430899 25
1794430904 25
1794430909 25
1794430914 25
1794430919 38
```
</details>

---

