---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:15:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 45-62 cores)</summary>

```
1794841837 62
1794841842 62
1794841847 62
1794841852 62
1794841857 62
1794841862 62
1794841867 60
1794841872 60
1794841877 60
1794841882 58
1794841887 58
1794841892 58
1794841897 58
1794841902 60
1794841907 60
1794841912 60
1794841917 60
1794841922 45
1794841927 45
1794841932 45
```
</details>

---

