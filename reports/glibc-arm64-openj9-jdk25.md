---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:39:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 12 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1795537872 54
1795537877 54
1795537882 54
1795537887 54
1795537892 54
1795537897 54
1795537902 54
1795537907 54
1795537912 49
1795537917 49
1795537922 49
1795537927 49
1795537932 49
1795537937 49
1795537942 49
1795537947 49
1795537952 49
1795537957 49
1795537962 54
1795537967 54
```
</details>

---

