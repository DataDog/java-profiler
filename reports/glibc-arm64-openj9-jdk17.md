---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 07:54:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795610940 64
1795610945 64
1795610950 64
1795610955 64
1795610960 64
1795610965 64
1795610970 64
1795610975 64
1795610980 64
1795610985 64
1795610990 64
1795610995 64
1795611000 64
1795611005 64
1795611010 64
1795611015 64
1795611020 64
1795611025 64
1795611030 64
1795611035 64
```
</details>

---

