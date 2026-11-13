---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:46:24 EST

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1794580877 76
1794580882 76
1794580887 74
1794580892 74
1794580897 74
1794580902 74
1794580907 74
1794580912 74
1794580917 74
1794580922 74
1794580927 74
1794580932 74
1794580937 74
1794580942 74
1794580947 74
1794580952 74
1794580957 74
1794580962 74
1794580967 74
1794580972 74
```
</details>

---

