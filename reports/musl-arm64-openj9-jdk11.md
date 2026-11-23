---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:46:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 10 |
| Allocations | 200 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795451814 64
1795451819 64
1795451824 64
1795451829 64
1795451834 64
1795451839 64
1795451844 64
1795451849 64
1795451854 64
1795451859 64
1795451864 64
1795451869 64
1795451874 64
1795451879 64
1795451884 64
1795451889 64
1795451894 64
1795451899 64
1795451904 64
1795451909 64
```
</details>

---

