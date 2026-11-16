---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:15:47 EST

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794841827 38
1794841832 38
1794841837 38
1794841842 38
1794841847 38
1794841852 38
1794841857 43
1794841862 43
1794841867 43
1794841872 43
1794841877 43
1794841882 43
1794841887 43
1794841892 43
1794841897 43
1794841902 43
1794841907 43
1794841912 43
1794841917 43
1794841922 43
```
</details>

---

