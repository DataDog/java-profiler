---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:15:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 9 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (4 unique values: 43-53 cores)</summary>

```
1794841832 46
1794841837 43
1794841842 43
1794841847 43
1794841852 43
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
1794841907 53
1794841912 53
1794841917 53
1794841922 53
1794841927 50
```
</details>

---

